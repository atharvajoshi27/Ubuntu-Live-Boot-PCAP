#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_message_generator(char *char_array, int size){
	srand(time(NULL));
	short selector, i;
	for(i = 0; i < size; i ++){
		selector = random() % 2;
		if(selector){
			char_array[i] = 'A' + rand() % 26;
		}
		else{
			char_array[i] = 'a' + rand() % 26;
		}
	}
	return;
}

void print_char_array(char *char_array, int size){
	int i;
	for(i = 0; i < size; i += 1){
		printf("%c", char_array[i]);
	}
	printf("\n");
}

int main(){
	char message[6];
	print_char_array(message, 6);
	random_message_generator(message, 6);
	print_char_array(message, 6);
	return 0;
}
