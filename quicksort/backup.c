#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
        char value;
} item;

void printArray(item* head, int length){
	int i;
	for(i = 0; i < length; i++){
		printf("%c ", (head + i)->value);
	}
	printf("\n");
}

void swap(item* ptr1, item* ptr2) {
	item tmp;
        tmp.value = ptr1->value;
        ptr1->value = ptr2->value;
        ptr2->value = tmp.value;
}

int partition(item* array, int count){
	int current, counter = 0;
	item pivot;
	int equal = 1;
	pivot.value = (array + rand()%count)->value;

	for(current = 0; current < count; current ++){
		//Checking if all values are equal
		if((array + current)->value != pivot.value) equal = 0;
		if((array + current)->value <= pivot.value){
			swap((array + current), (array + counter));
			counter += 1;
		}
	}
	if(equal) return -1;
	else return counter;
}

void quicksort(item* array, int count){
//debug	printArray(array, count);
	if(count <= 1) return;
	if(2 == count){
		if(array->value > (array + 1)->value) swap(array, (array + 1));
		return;
	}
	int partitioneer = partition(array, count);

	//All elements are equal
	if(-1 == partitioneer) return;
	quicksort(array, partitioneer);
	quicksort((array + partitioneer), (count - partitioneer));
}


int main() {
	int amount, i;
	char placeholder;

	printf("Enter the number of arguments: ");
	if(! scanf("%i", &amount)){
		perror("Scanf failed");
		return -1;
	}

	scanf("%c", &placeholder);

	if(0 == amount){
		printf("Sorted 0 elements!\n");
		return 1;
	}

        item* list = malloc(amount * sizeof(item));
        if (!list){
		perror("Memory allocation error");	
		return -1;
	}

	for(i = 0; i < amount; i++){
		printf("Enter the argument number %i: ", i+1);
		if(! scanf("%c", &((list + i)->value))){
			perror("Scanf failed");
			return -1;
		}
		scanf("%c", &placeholder);
	}
//debug	printArray(list, amount);
        quicksort(list, amount);

        for (i = 0; i < (amount - 1); i++) {
	        printf("%c ", (list+i)->value);
	        if ((list+i)->value > (list+i+1)->value){
		        printf("\n\x1b[31m%c\x1b[0m\n", (list + i + 1)->value);
		        printf("Error: sorting failed.\n");
		        return -1;
	        }
        }
	printf("%c\n\n", (list + amount - 1)->value);
	if(1 == amount){
		printf("Sorted 1 element\n");
		free(list);
		return 1;
	}
	printf("Sorted %i elements\n", amount);
        free(list);
        return 1;
}






