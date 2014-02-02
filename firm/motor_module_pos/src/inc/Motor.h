// pins

#define PIN_M_EN		PD7
#define PIN_M_1A		PD5
#define PIN_M_2A		PD6

extern long target_pos;

void motor_init(void);

void motor_forward(int speed);
void motor_backward(int speed);
void motor_stop(void);
void motor_brake(void);
