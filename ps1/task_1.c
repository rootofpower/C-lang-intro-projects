#include<superkarel.h>
#include<stdbool.h>

#define DEF_STEP 100

void stepping_forward(void);
void stepping_backward(void);
void turn_right(void);
void pick_upping_beepers(void);
void look_north(void);
void look_west(void);
void step_and_put(void);
void look_east(void);

int main(int argc, char *argv[]){
	turn_on("task_1.kw");
	set_step_delay(DEF_STEP);
	look_north();
	if(no_beepers_present()) step_and_put();
	else{
		look_west();
		turn_off();
	}
	stepping_forward();
	look_north();
	pick_upping_beepers();	
	stepping_backward();
	look_west();
	turn_off();
	return 0;
}

void turn_right(void){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(DEF_STEP);
	turn_left();
}

void stepping_forward(void){
	while(no_beepers_present()){
		if(right_is_clear()) turn_right();
		if(!left_is_blocked() && front_is_blocked()) turn_left();
		else if (front_is_blocked()){
			turn_left();
			turn_left();
		}
		if(front_is_clear()) step();	

	}

}
	
void pick_upping_beepers(void){
	while(beepers_present()) pick_beeper();
}

void look_north(){
	while(!facing_north()) turn_left();
}

void stepping_backward(){
	while(1){
		if(left_is_clear()) turn_left();
		if(!right_is_blocked() && !front_is_clear()) turn_right();
		else if(!front_is_clear()){
			turn_left();
			turn_left();
		}
		if(front_is_clear()) step();
		if(beepers_present()){
			while(beepers_present()) pick_beeper();
			break;
		} 
	}
}

void look_west(){
	while(!facing_west()) turn_left();
}

void step_and_put(){
	put_beeper();
	if(front_is_clear() && right_is_blocked()) step();
	else {
	look_east();
	step();
	}
}

void look_east(){
	while(!facing_east()) turn_left();
}








