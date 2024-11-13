#include<superkarel.h>
#define SPEED 100

void turn_right(void);
void look_north(void);
void look_west(void);
void look_south(void);
void look_east(void);
void stepping(void);

int main(int argc, char *argv[]){
	turn_on("task_6.kw");
	set_step_delay(SPEED);
	while(front_is_clear()){
		stepping();
		if(beepers_present()){//1
			pick_beeper();
			look_north();
			if(beepers_present()){//2
				pick_beeper();
				look_west();
				if(beepers_present()){//3
					pick_beeper();
					look_south();
					if(beepers_present()){//4
						pick_beeper();
						look_east();
						if(beepers_present()){ //5
							pick_beeper();
							turn_off();
						}
					}
				}
			}
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

void look_north(void){
	while(!facing_north()) turn_left();
}

void look_west(void){
	while(!facing_west()) turn_left();
}

void look_south(void){
	while(!facing_south()) turn_left();
}

void look_east(void){
	while(!facing_east()) turn_left();
}

void stepping(void){
	while(no_beepers_present()) step();
}
