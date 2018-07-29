#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/alt_alarm.h>


//#include"max_pooling.h"
#include"activation_fun.h"
#include"fully_connected.h"
//#include"convolution.h"
#include"batch_norms.h"
#include "movement.h"



float max_10(int length, const float vec[length])
{
	
   float max_out = vec[0];
   int pos = 1;
   int i;
   for(i=1;i<length;i=i+1)
   {
        if (vec[i] > max_out)
        {
        	pos = i + 1;
        	max_out = vec[i];
        }
   }
   return pos;
}

int main(void)
{
	float* un_vect3;
	float* un_vect35;
	float* un_vect4;
	float* un_vect5;
	float* un_vect55;
	float* un_vect6;
	float* un_vect7;
	
	int final_out;
    int i,j;
    
    static const float inp[4][32] = {{0.442492,0,0.628438,0.253064,0,0,0,0,0,0,0,0,0.00908585,0,0,1.00053e-42,1.60643e-18,0,0,0,0,0,2.37156e-06,0.168486,0,0,0,0,0,0,0,0},{0.277291,0,0.266489,0.319079,0,0,0.505466,0,0,0,0,0,0.00845936,0.0130044,0.442407,1.00053e-42,1.60644e-18,0,0.194521,0,0,0,2.37156e-06,0.231257,0,0.0876253,0,0,0,0,0,0},{0.182863,0,0.0204466,0,0.000117886,0,0.158559,0,0,0,0,0,0.00854225,0.415741,0.153691,1.00053e-42,1.60643e-18,0,0,0,0,0,2.37156e-06,0.132753,0,0,0,0,0,0,0.0523204,0},{0.142805,0.0323475,0.161221,0.255,0.00227299,0,0,0,0,0,0,0,0.0109124,0.000479074,0,1.00053e-42,1.60644e-18,0,0,0,0,0,2.37156e-06,0.503747,0,0,0,0,0,0,0,0}};

    static const float mean2[16] = {0.0171751,0.218673,-3.65938e-08,-3.65467e-12,0.023393,-3.93884e-16,-1.8007e-18,-3.09291e-15,-1.19799e-09,0.0574816,-2.58292e-08,0.0781449,-3.09892e-14,-2.13678e-13,0.180576,-1.09185e-12 };
    static const float variance2[16] = {0.0168112466356135,0.0945849293817108,3.69957772585167e-09,5.57113808772045e-11,0.0239716790267230,5.84627536221105e-14,8.14769276272103e-17,1.24255656989636e-12,6.29460235978283e-12,0.0790024359982385,1.54184378520902e-13,0.0679508399386208,4.45224892523102e-12,7.08715485137811e-11,0.136117088143116,4.61221800672035e-11};
    static const float affine_r2[16] = {0.141512,0.316052,-8.67964e-42,-1.03136e-42,0.138144,-2.39482e-42,2.77597e-42,-2.9161e-42,-2.89228e-42,0.264392,4.13011e-06,0.23389,2.08179e-14,3.37713e-42,0.190538,-8.55773e-42 };
    static const float affine_c2[16] = {0.0439228,0.0946699,4.76021e-42,-6.79349e-42,-0.0401458,-2.96515e-42,5.2829e-42,6.46139e-42,-5.13856e-42,0.163904,6.97939e-13,0.119168,-5.67453e-17,6.97847e-43,0.40046,9.12245e-43 };

    static const float mean3[8] = {-0.0632374,-2.38747e-09,0.115511,0.092088,-0.169158,0.104168,-0.135601,0.0550785 };
    static const float variance3[8] =  {0.0708, 0.0000, 0.0535, 0.0995, 0.0745, 0.0772, 0.0723, 0.0740};
    static const float affine_r3[8] = {1.12644,2.48618e-41,1.34908,1.15442,1.33413,1.2364,1.56656,1.19202 };
    static const float affine_c3[8] = {0.802881,-3.59344e-33,0.69274,0.89005,0.850165,0.747865,0.728998,0.949102 };



    static const float bias_fc2[16] = {-9.05632e-05,5.17794e-05,9.7691e-07,-1.5289e-15,-2.39265e-05,-1.22344e-14,2.67102e-17,3.06051e-15,4.55131e-08,-7.44568e-05,5.06537e-07,-6.25097e-05,9.07402e-20,-2.85163e-15,2.21367e-05,-3.60706e-19 };
    static const float bias_fc3[8] = {-7.93103e-05,3.2407e-08,-5.82372e-06,-2.68044e-05,3.87592e-05,-1.72586e-05,3.61977e-05,-2.6987e-06 };
    static const float bias_fc4[4] = {-0.0603522,0.0478874,0.279656,-0.342277 };



    static const float weight_fc2[16][32] = {{0.0258486,0.00855987,0.0365778,-0.0570332,-0.00571106,1.17289e-42,-0.0410533,2.94207e-06,7.80034e-05,0.0115584,0.00086485,0.0232137,-0.00708458,-0.013059,-0.0136971,5.54214e-42,-4.62835e-18,0.0111777,0.104591,-1.28164e-07,7.13969e-15,0.010956,1.1057e-05,0.0498366,2.53443e-06,0.0233057,-2.11542e-25,0.00998965,-7.06254e-42,-2.66626e-16,0.0628843,2.03194e-13 },
    {0.375064,0.162042,0.309916,0.0167349,0.00130797,-6.15795e-09,0.164273,4.59559e-07,-0.000313697,-0.105141,0.000226428,0.0141046,0.00276894,0.174289,0.0118763,6.95044e-43,-6.222e-20,0.00620823,-0.0930455,-1.53706e-05,4.39924e-16,-0.00539757,5.95689e-11,-0.0173001,3.91479e-10,-0.0604529,-1.55248e-27,-0.00507565,-4.71817e-42,6.72896e-17,-0.0196037,1.55944e-18 },
    {5.74224e-41,-3.60344e-41,1.68576e-41,-1.87788e-41,-2.05422e-11,-8.3413e-08,8.58435e-42,-6.41057e-12,-7.99406e-16,-1.9394e-42,-1.55121e-05,-2.04786e-41,1.01168e-18,-3.19188e-41,1.26215e-41,-6.64197e-11,3.92053e-13,-2.30216e-18,7.18165e-42,1.54511e-13,1.03542e-18,-3.79831e-18,-3.69758e-13,3.36312e-44,-7.63278e-10,-3.09673e-41,-4.87803e-20,1.70658e-12,5.14258e-19,-4.14783e-19,-2.04299e-09,-2.19094e-07 },
    {-9.63112e-42,-3.34966e-41,-8.55353e-42,-4.86811e-42,-1.44264e-17,-3.16007e-41,2.45788e-42,2.77963e-11,-3.50988e-07,-6.28903e-42,-1.22322e-14,-1.13659e-41,-9.28611e-18,5.16799e-42,-7.54459e-42,-2.48912e-17,1.62996e-16,-7.65926e-11,-5.24506e-42,-1.36794e-11,9.88706e-19,1.11695e-06,-3.36312e-44,5.55054e-42,1.3201e-11,4.54301e-42,4.35846e-41,-4.51123e-18,3.03383e-12,1.64288e-11,3.19784e-09,-1.03135e-05 },
    {0.0598128,0.0551332,-0.032725,-0.0531388,-0.00232065,-8.35499e-22,0.00160992,-3.63627e-07,-4.43726e-05,-0.056997,0.000814793,0.113313,-0.00282352,0.064393,0.0886328,-4.41549e-42,3.96416e-20,0.00239451,-0.0472822,-3.99894e-06,-8.16987e-16,0.00227184,5.68775e-12,0.0420967,-5.68229e-06,0.0202996,-8.95665e-28,-0.00949618,8.11072e-42,-1.60843e-16,-0.00413625,-4.10603e-18 },
    {2.00386e-43,4.58645e-42,-3.47942e-42,2.82922e-42,2.19292e-11,4.47449e-41,-4.62989e-42,-2.11839e-19,2.24655e-18,5.42583e-42,8.8582e-09,4.12262e-42,1.03506e-14,5.70469e-42,-1.48117e-42,1.03118e-11,-1.16591e-06,3.5715e-18,2.70451e-42,-3.53229e-13,1.15153e-15,-1.52042e-11,2.09634e-41,-3.77089e-42,-8.76178e-08,-2.19443e-42,-5.90227e-42,9.01068e-12,1.1438e-10,4.39852e-15,2.78029e-13,-9.79195e-21 },
    {-4.93958e-42,-1.80207e-42,-1.31722e-43,1.14626e-42,-2.23143e-20,1.46224e-39,-6.4754e-42,1.99405e-17,-8.85402e-13,1.95902e-42,1.36835e-18,6.98267e-42,-2.55039e-17,3.8844e-42,-5.40621e-42,2.61953e-12,-9.24598e-18,-4.98546e-19,-5.92189e-42,-1.34305e-05,-8.04011e-14,4.80192e-12,1.58795e-41,-2.1566e-42,-8.33516e-18,7.1186e-43,-1.55396e-10,-5.42973e-14,7.35364e-18,-2.83209e-12,-2.49262e-17,-2.34333e-17 },
    {-2.07126e-41,-2.03104e-41,-3.29165e-42,-8.94589e-42,3.53072e-11,-1.62927e-14,-3.70083e-42,-1.31552e-11,1.10732e-13,1.82169e-42,-4.9092e-08,-2.38571e-41,6.83299e-19,9.64794e-42,-4.03994e-42,7.39527e-17,-8.78413e-06,-6.44374e-17,4.30759e-42,-9.33854e-11,-1.12804e-08,-1.46772e-16,-1.22912e-18,-2.20004e-43,5.58237e-18,1.05938e-42,-4.64186e-10,-9.89922e-18,-7.45825e-11,-1.66847e-10,4.65376e-12,7.15237e-14 },
    {2.88107e-42,1.55866e-41,-7.48153e-42,-1.07045e-41,1.07601e-19,-1.58235e-13,1.2707e-41,4.36434e-15,-4.63185e-41,-2.23087e-42,6.79067e-12,-2.28131e-42,-1.63354e-16,8.94869e-42,7.07516e-42,-9.27248e-07,6.57283e-16,-2.49555e-09,1.06807e-41,-1.33361e-12,-9.85416e-08,1.11932e-07,2.48008e-15,8.2004e-42,-3.42503e-08,3.10107e-42,-1.12385e-18,2.99483e-09,9.86844e-13,9.67888e-09,-4.47932e-24,3.33538e-19 },
    {-0.0217631,0.0301204,-0.115406,0.106332,-0.000369782,-3.29516e-09,-0.0617722,-1.98726e-07,-2.53673e-05,0.21869,-0.000662283,-0.177239,0.00637663,0.165194,-0.155936,1.01034e-42,-1.04942e-19,-0.00926666,0.100693,7.22796e-06,3.41535e-16,0.000158384,2.28367e-10,0.223466,1.04669e-08,0.302256,7.49721e-27,0.00122523,-2.17061e-42,-8.99043e-17,-0.0712725,3.247e-18 },
    {6.03418e-14,-2.09823e-14,1.36388e-13,5.2458e-14,-8.46691e-14,9.00895e-42,-6.12474e-14,1.89272e-13,-1.6377e-41,-5.71817e-14,-1.61052e-15,5.89801e-14,-2.74483e-13,7.46923e-14,4.94828e-14,-2.41079e-41,1.89831e-09,-2.66665e-16,9.76709e-15,-1.33143e-16,3.59029e-11,-2.69481e-16,-8.14381e-24,-4.88728e-14,2.95074e-08,1.05086e-13,-1.07765e-11,-5.6176e-14,-2.56287e-07,4.91049e-19,6.69899e-14,-1.95373e-17 },
    {0.0882839,0.148248,-0.0600275,0.136762,-1.4498e-05,-3.24102e-13,-0.0451113,-7.37845e-08,7.13143e-05,0.155922,0.00177264,-0.0262443,-0.0101289,0.0145557,-0.0883963,-3.92364e-43,-6.71616e-20,0.00554413,-0.189096,4.60618e-06,-6.92528e-16,-0.00456147,5.57352e-11,0.24559,-7.21678e-09,0.044105,6.23456e-27,-0.00984429,5.65144e-42,1.35811e-17,-0.0974756,2.26069e-18 },
    {-3.35055e-33,3.13956e-31,-7.97799e-31,1.19457e-31,-1.53374e-11,2.75681e-21,-1.5493e-31,1.96539e-09,3.70901e-13,3.64149e-31,-1.08625e-16,1.73182e-31,1.21138e-15,9.72365e-31,4.62232e-31,-2.80785e-10,-1.01127e-06,-8.50631e-14,-2.55787e-30,-2.82812e-19,-1.41239e-13,3.3075e-18,-1.67557e-09,-6.24536e-31,-1.27956e-10,1.80685e-31,-2.20275e-06,-1.36143e-17,-2.9386e-07,-5.77985e-15,2.66744e-11,-3.31445e-09 },
    {6.58891e-42,1.16378e-41,-5.52392e-42,-5.45666e-42,1.07914e-09,1.72225e-26,4.51779e-42,6.23611e-09,5.72128e-06,2.02347e-42,6.00593e-19,-4.82047e-43,5.58931e-13,2.56297e-42,2.74935e-42,2.29729e-18,3.02317e-07,-3.8792e-11,-3.57051e-42,-3.53324e-08,-1.2508e-14,1.46378e-11,-5.18242e-41,-4.08759e-42,8.30532e-12,2.97075e-42,-2.97195e-09,-3.8221e-18,1.78984e-09,-8.32735e-17,3.36342e-10,-4.22922e-07 },
    {0.086169,-0.100404,-0.06908,0.35767,0.00119355,-4.46734e-10,0.261179,-2.91583e-07,0.000150503,0.135833,0.00053583,0.130956,-0.00340822,-0.171128,0.275764,4.37906e-42,-8.01724e-21,-0.00557305,0.174369,-2.93963e-05,-1.70894e-15,-0.0145868,-1.30886e-10,-0.099286,-2.65678e-10,-0.051074,-2.36756e-27,-0.00936779,-9.79508e-43,-2.42241e-17,-0.0843704,-4.12191e-19 },
    {8.99213e-42,-4.4204e-41,6.39412e-42,-7.40026e-42,1.03048e-08,5.46274e-16,-1.00263e-41,1.47979e-18,-3.14133e-14,-6.21055e-42,-2.84691e-12,-1.92174e-41,-2.62118e-15,6.56648e-42,-7.48293e-43,1.39435e-14,-3.74585e-17,-2.98191e-14,-2.19583e-42,-2.40047e-12,-3.55743e-19,3.71886e-11,5.88085e-11,-6.93222e-42,2.64444e-15,-4.47855e-42,2.13506e-18,2.4363e-09,3.46028e-15,-3.50996e-13,4.68487e-10,-6.32581e-21 }};



    static const float weight_fc3[8][16] = {{0.0373114,-0.14218,2.8913e-41,5.77335e-43,-0.00112834,-1.73621e-42,-3.54388e-42,-8.28448e-42,-1.86092e-42,-0.186936,-2.45041e-13,-0.181806,4.61976e-21,-2.68209e-42,0.0685517,-5.16238e-42 },
    {-1.58594e-16,-3.32724e-41,1.0562e-17,2.18989e-15,-2.42691e-41,-2.04091e-08,8.71096e-15,-1.50475e-09,-1.03969e-16,-3.49274e-41,-1.80579e-17,3.2129e-41,-9.23505e-16,3.78736e-13,-1.19811e-41,-5.3423e-19 },
    {-0.0120002,-0.0192585,-1.06078e-42,-3.79331e-42,0.0845635,-1.73901e-42,2.21265e-42,-1.35716e-41,-1.0116e-41,0.0403336,-7.78434e-13,-0.0236403,-5.20167e-21,1.1827e-42,0.279683,6.23157e-42 },
    {-0.130703,0.303535,-2.15702e-41,1.1925e-42,-0.0494058,-4.70556e-42,-1.55124e-42,8.5241e-42,-1.37159e-41,0.172903,5.30219e-14,0.292729,3.20432e-23,-1.34104e-42,-0.0844178,1.09638e-41 },
    {-0.120358,0.120172,-1.72079e-41,8.36575e-43,0.144326,-3.13891e-43,-3.94325e-42,1.08503e-41,-7.79122e-43,-0.167597,1.24778e-13,-0.0376107,-1.37337e-22,-1.91417e-42,-0.364201,-6.49362e-42 },
    {-0.0384066,0.301346,-1.78553e-41,4.12823e-42,0.100706,2.01927e-42,-1.85672e-42,-1.18382e-41,1.78105e-42,0.0140525,-7.78331e-15,0.0459911,-1.22755e-21,-4.18288e-42,0.096156,2.47189e-42 },
    {0.0603923,-0.0525288,-6.32546e-42,-2.53355e-42,-0.0810741,3.33229e-42,3.66019e-42,1.21086e-41,-7.32178e-42,0.00437031,3.17066e-13,0.019239,6.32618e-21,-9.66896e-43,-0.32909,3.62516e-42 },
    {0.0162525,-0.130797,1.37159e-41,1.81608e-42,-0.0421195,3.83956e-42,-9.3887e-43,-1.49378e-41,-1.01846e-41,0.313976,-1.21035e-12,-0.0918679,-2.31623e-21,5.07971e-42,0.0745775,-6.02698e-42 }};

    static const float weight_fc4[4][8] = {{-0.140569,1.54272e-33,0.179656,0.743521,0.150634,0.880231,-0.761842,-1.19109 },
    {0.701844,-1.30941e-33,0.829049,-0.535903,-1.30702,-0.0333677,-1.06224,0.341895 },
    {0.343071,-1.71358e-33,-0.910451,-1.03395,0.797272,-0.856785,0.609588,-0.453792 },
    {-1.19674,1.92178e-33,-0.779409,0.516494,-0.0217443,-0.615055,0.75041,0.741189 }};

    int iter = 0;
    //int movement[5] = {1,2,3,1,4};
    for (iter=0;iter<sizeof(movement)/sizeof(movement[0]);iter++){
    	if(movement[iter]==-1){
    		printf("%d\n",movement[iter]);
    	}
    	else if(movement[iter]==0){
    		usleep(2000000);
    	}
    	else{
		   un_vect3 = fully_connect(16,32,inp[movement[iter]-1],weight_fc2,bias_fc2);
		   un_vect35 = batch_norm(16,un_vect3,mean2,variance2,affine_r2,affine_c2);
		   un_vect4 = activation_1d(16, un_vect35);

			un_vect5 = fully_connect(8,16,un_vect4,weight_fc3,bias_fc3);
			un_vect55 = batch_norm(8,un_vect5,mean3,variance3,affine_r3,affine_c3);
			un_vect6 = activation_1d(8,un_vect55);

			un_vect7 = fully_connect(4,8,un_vect6,weight_fc4,bias_fc4);
			final_out = max_10(4,un_vect7);
			printf ("%d\n", final_out);
    	}
		usleep(500000);
    }
   return(0);

}
