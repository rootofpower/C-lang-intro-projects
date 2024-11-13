#include<superkarel.h>
#define SPEED 50

void find_corner(void);
void turn_right(void);
void look_west(void);
void put_beepers(void);
void seek_center(void);
void look_back(void);
void look_north(void);
void double_step(void);
_Bool check_is_corner(void);
void look_east(void);

int main(int argc, char *argv[]){
	turn_on("task_5.kw");
	set_step_delay(SPEED);
	look_east();
	if(front_is_clear() && right_is_clear() && left_is_clear()){
		find_corner();
		put_beepers();
		seek_center();
		look_north();
		seek_center();	
		turn_off();
	}
	else {
		while(front_is_clear()) step();
		if(check_is_corner()) {
			put_beepers();
			seek_center();
			look_north();
			seek_center();
			turn_off();
		}
	}

	turn_off();
}

void find_corner(void){
	while(front_is_clear()) step();
	if(front_is_blocked() && right_is_clear()){
		turn_right();
		while(front_is_clear()) step();
	}
	if(front_is_blocked() && left_is_clear()){
		turn_left();
		while(front_is_clear()) step();
	}
	look_west();
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

void put_beepers(void){
	while(1){
		if(no_beepers_present()) put_beeper();
		if(front_is_clear()) step();
		if(front_is_blocked() && right_is_clear()) turn_right();
		if(beepers_present()) break;
	}

}

void double_step(void){
	step();
	step();
}

void seek_center(void){
	double_step();
	if(front_is_clear()) seek_center();
	look_back();
	step();
	look_back();
}

void look_back(void){
	turn_left();
	turn_left();
}

void look_north(void){
	while(!facing_north()) turn_left();
}
_Bool check_is_corner(void){
	look_north();
	look_back();
	while(front_is_clear()) step();
	turn_left();
	while(front_is_clear()) step();
	if(front_is_blocked() && right_is_blocked()){
		look_west();       
		return 1;
	}
	else return 0;
}

void look_east(void){
	while(!facing_east()) turn_left();
}
