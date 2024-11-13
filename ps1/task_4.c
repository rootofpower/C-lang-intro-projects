#include<superkarel.h>
#define STEP_DELAY 20

void search_beeper(void);
void one_step(void);
void put_beepers(void);
void turn_right(void);
void look_north(void);
void look_south(void);
_Bool is_corner(void);

int main(int argc, char *argv[]){
	turn_on("task_4.kw");
	set_step_delay(STEP_DELAY);
	while(1){	
		search_beeper();
		if(beepers_present()){
			put_beepers();
			one_step();
		}
		else {
			look_south();
			while(front_is_clear()) step();
			one_step();
		}
		if(is_corner()){
			search_beeper();
			if(beepers_present()) put_beepers();
			look_south();
			while(front_is_clear()) step();
			while(!facing_east()) turn_left();
			break;
		}	

	}
	turn_off();
}

void turn_right(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(STEP_DELAY);
	turn_left();
}

void search_beeper(void){
	look_north();
	while(front_is_clear()){
		step();
		if(beepers_present()) break;
	}
}

void look_north(void){
	while(!facing_north()) turn_left();
}

void look_south(void){
	while(!facing_south()) turn_left();
}
void put_beepers(void){
	while(front_is_clear()) step();
	look_south();
	while(1){
		if(front_is_blocked()&& no_beepers_present()){
			put_beeper();
			break;
		}
		else if(front_is_blocked() && beepers_present()) break;
		if(front_is_clear() && no_beepers_present()) put_beeper();
		else step();
		
	}
}

void one_step(){
	while(!facing_east()) turn_left();
	if(front_is_clear()) step();
}

_Bool is_corner(void){
	look_south();
	if(front_is_blocked() && left_is_blocked()) return 1;
	else return 0;
}
