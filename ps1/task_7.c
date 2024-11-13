#include<superkarel.h>
#define SPEED 50

void put_beepers(void);
void look_west(void);
void look_east(void);
void turn_right(void);
void turn_back(void);
void check(void);
void check_beepers(void);

int main(int argc, char *argv[]){
	turn_on("task_7.kw");
	set_step_delay(SPEED);
	put_beepers();
	look_west();
	while(front_is_clear()) step();
	look_east();
	check();
	look_east();
	while(beepers_present()) pick_beeper();
	check_beepers();
	turn_off();
}

void put_beepers(void){
	look_east();
	while(1){
	if(left_is_clear()) {
		turn_left();
		step();
		put_beeper();
		put_beeper();
		turn_back();
		step();
		look_east();
		}
	else;
	if(front_is_clear()){
		put_beeper();
		step();
	}
	else break;
	}
}

void turn_right(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(SPEED);
	turn_left();
}

void look_west(void){
	while(!facing_west()) turn_left();
}

void look_east(void){
	while(!facing_east()) turn_left();
}

void turn_back(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(SPEED);
}

void check(void){
	while(1){
		if(left_is_clear()){
			turn_left();
		}
		if (right_is_clear() && front_is_blocked()){
			turn_right();
			continue;
		}
		else if (front_is_blocked()) turn_back();
		step();
		if(beepers_present()){
			if(front_is_clear()) pick_beeper();
			else if(front_is_blocked()&& left_is_blocked()) break;
		}
	}
}

void check_beepers(void){
	while(1){
		if(left_is_clear()){
			turn_left();
			step();
			if(beepers_present()){
				pick_beeper();
				if(beepers_present()) {
					while(beepers_present()) pick_beeper();
					turn_back();
					step();
					look_east();
				}
				else{
					put_beeper();
					turn_back();
					step();
					look_east();
				}

			}
			else {
				turn_back();
				step();
				look_east();
			}
		}
		if(front_is_blocked()) break;
		else step();
	}
}
