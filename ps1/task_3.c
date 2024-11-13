#include<superkarel.h>

#define STEP_SPEED 20
void turn_right(void);
void pick_up_beepers(void);
_Bool is_ceil(void);
void look_east(void);
void put_down_beepers(void);
void one_step(void);
void look_west(void);
void step_down(void);
void back_to_spawn(void);
_Bool is_beeper_up(void);
void check_is_end(void);
void look_south(void);
void go_end(void);
void look_north(void);

int main(int argc, char *argv[]){
	turn_on("task_3.kw");
	set_step_delay(STEP_SPEED);
	while(1){
		pick_up_beepers();
		put_down_beepers();
		if(front_is_blocked() && left_is_blocked()){
//			back_to_spawn();
			check_is_end();
			break;
		}
		else step_down();
	}
	check_is_end();
	turn_off();
}

void turn_right(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(STEP_SPEED);
	turn_left();
}

_Bool is_ceil(void){
	while(!facing_north()) turn_left();
	if(facing_east()){
		if(front_is_blocked()){
			turn_right();
			return 1;
		}
		else {
			turn_right();
			return 0;
		}
	}
	else{
		if(front_is_blocked()){
			turn_left();
			return 1;
		}
		else {
			turn_left();
			return 0;
		}
	}
}
void pick_up_beepers(void){
	look_east();
	while(1){
		if(front_is_clear()){
			step();
			if(beepers_present()) pick_beeper();
		}
		else {
			if(front_is_clear()) step();
			else break;
		}
	}
}

void look_east(void){
	while(!facing_east())turn_left();
}

void put_down_beepers(void){
	look_west();
	while(1){
		if(is_ceil() && beepers_in_bag()) {
			put_beeper();
			step();
		}
		else if(is_beeper_up() && beepers_in_bag()){
			put_beeper();
			step();
			continue;
		}
		if(!is_ceil()&& front_is_clear()) step();

		if(no_beepers_in_bag()){
			while(front_is_clear()) step();
			break;
		}
			
	}
}

void look_west(void){
	while(!facing_west()) turn_left();
}
void step_down(void){
	turn_left();
	step();
	turn_left();
}
_Bool is_beeper_up(void){
	turn_right();
	if(front_is_clear()){
		step();
		if(beepers_present()){
			turn_left();
			turn_left();
			step();
			turn_right();
			return 1;
		}
		else{
			turn_left();
			turn_left();
			step();
			return 0;
		}
	}
	else turn_left();
	return 0;
}

void back_to_spawn(void){
	look_east();
	while(front_is_clear())step();
	turn_left();
	while(front_is_clear())step();
	turn_left();
	while(front_is_clear())step();
	look_east();
}

void check_is_end(void){
	look_south();
	while(front_is_clear()) step();
	look_east();
	go_end();	
}

void look_south(void){
	while(!facing_south()) turn_left();
}
void go_end(void){
	while(no_beepers_present()&& front_is_clear()) step();
	if(beepers_present()){
		look_north();
		while(front_is_clear()) step();
		look_west();
		while(front_is_clear()) step();
		look_east();
	}
	else{
		look_west();
		while(front_is_clear()) step();
		look_north();
		step();
		look_east();
		go_end();
	}
}

void look_north(void){
	while(!facing_north()) turn_left();
}
