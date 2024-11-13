#include<superkarel.h>

#define SPEED 100

void turn_right(void);
void going(void);
void turn_back(void);
void look_north(void);

int main(int argc, char *argv[]){
	turn_on("task_2.kw");
	set_step_delay(SPEED);	
	going();	
	turn_back();	
	look_north();
	turn_off();
	return 0;
}

void going(void){
	while(1){
		if(beepers_present()){
			pick_beeper();
			break;
		}	
		if(front_is_clear()) {
			step();
		}
		if(left_is_clear()){
			turn_left();
			continue;
		}
	
	}
}

void turn_right(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(SPEED);
	turn_left();
}

void turn_back(void){
	turn_left();
	turn_left();
	 while(1){
		if(front_is_blocked() && right_is_blocked() && left_is_blocked())
		       break;	
	 	if(front_is_clear()) step();
		if(front_is_blocked() && right_is_clear()){
			turn_right();
			continue;
		}

	 }
}

void look_north(void){
	while(!facing_north()) turn_left();
}
