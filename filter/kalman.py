import numpy as np
import matplotlib.pyplot as plt
class kalman_filter2:
    def __init__(self,Q,R):
        self.Q = Q
        self.R = R
        
        self.P_k_k1 = 1
        self.Kg = 0
        self.P_k1_k1 = 1
        self.x_k_k1 = 0
        self.ADC_OLD_Value = 0
        self.Z_k = 0
        self.kalman_adc_old=0
        
    def kalman(self,ADC_Value):
       
        self.Z_k = ADC_Value
        
        if (abs(self.kalman_adc_old-ADC_Value)>=60):
            self.x_k1_k1= ADC_Value*0.382 + self.kalman_adc_old*0.618
        else:
            self.x_k1_k1 = self.kalman_adc_old;
    
        self.x_k_k1 = self.x_k1_k1
        self.P_k_k1 = self.P_k1_k1 + self.Q
    
        self.Kg = self.P_k_k1/(self.P_k_k1 + self.R)
    
        kalman_adc = self.x_k_k1 + self.Kg * (self.Z_k - self.kalman_adc_old)
        self.P_k1_k1 = (1 - self.Kg)*self.P_k_k1
        self.P_k_k1 = self.P_k1_k1
    
        self.kalman_adc_old = kalman_adc
        
        return kalman_adc
class kalman_filter:
    def __init__(self,Q,R):
        self.Q = Q
        self.R = R
        
        self.P_k_k1 = 1
        self.Kg = 0
        self.P_k1_k1 = 1
        self.x_k_k1 = 0
        self.ADC_OLD_Value = 0
        self.Z_k = 0
        self.kalman_adc_old=0
        
    def kalman(self,ADC_Value):
       
        self.Z_k = ADC_Value
        
        if (abs(self.kalman_adc_old-ADC_Value)>=60):
            self.x_k1_k1= ADC_Value*0.382 + self.kalman_adc_old*0.618
        else:
            self.x_k1_k1 = self.kalman_adc_old;
    
        self.x_k_k1 = self.x_k1_k1
        self.P_k_k1 = self.P_k1_k1 + self.Q
    
        self.Kg = self.P_k_k1/(self.P_k_k1 + self.R)
    
        kalman_adc = self.x_k_k1 + self.Kg * (self.Z_k - self.kalman_adc_old)
        self.P_k1_k1 = (1 - self.Kg)*self.P_k_k1
        self.P_k_k1 = self.P_k1_k1
    
        self.kalman_adc_old = kalman_adc
        
        return kalman_adc

def np_move_avg(a,n,mode="same"):
    return(np.convolve(a, np.ones((n,))/n, mode=mode))
LEN = 500
if __name__ == '__main__':
    kalman_filter =  kalman_filter(0.001,0.1)
    kalman_filter2 =  kalman_filter2(0.001,3.9)
    # a= [100]*200
    a= []
    for i in range(LEN//2):
        a.append(100-i*0.1)
    for i in range(LEN//2):
        a.append(200-i*0.1)        
    array = np.array(a)
    
    s = np.random.normal(0, 15, LEN)
    test_array = array + s
    kalman1=[]
    kalman2=[]
    smooth=[]
    for i in range(LEN):
        kalman1.append(kalman_filter.kalman(test_array[i]))
    
    for i in range(LEN):
        kalman2.append(kalman_filter2.kalman(test_array[i]))        
    smooth = np_move_avg(test_array, 20)
    
    # plt.plot(kalman1, label='kalman1')   
    plt.plot(array, label='real')
    plt.plot(test_array, label='measure')
    plt.plot(smooth, label='smooth')  
    plt.plot(kalman2, label='kalman')   
    plt.legend()
    plt.show()
    # help(np.random.normal)
