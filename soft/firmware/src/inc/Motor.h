#define MOTOR_SLOWEST	0xFFF // the slowest speed cutoff

#define LEFT	1
#define RIGHT	-1

// pins

#define PIN_M_EN		PC0
#define PIN_M_1A		PD5
#define PIN_M_2A		PD6

typedef enum {
	POSITION,
	VELOCITY,
	ACCELERATION
} MotorMode;

typedef struct {
	MotorMode mode;
	int8_t dir;
	uint16_t inverse_speed;
	uint16_t target_speed;
	unsigned int ticks;
} Motor;

extern volatile Motor motor;

void motor_init(void);

void motor_stop(void);
void motor_brake(void);

void motor_set_pos(int8_t dir, unsigned int speed);
void motor_set_vel(int8_t dir, unsigned int speed);
void motor_set_accel(int8_t dir, unsigned int speed);
