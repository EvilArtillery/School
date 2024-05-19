#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

typedef struct dot{  //A dot, literally.
	double x, y;
} dot;

typedef struct line{ //A line using 3 arguments.
	//ax + by + c = 0;
	double a, b, c;
} line;


double dtd(dot a, dot b){ //Distance from Dot To Dot, from there comes the name.
	double dist;
	dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return dist;
}

double dtl(dot a, line b){ //Distance from Dot To Line, analogically to dtd.
	line h; //h stands for Height, or perpendicular.
	h.a = -b.b;
	h.b = b.a;
	h.c = -(h.a * a.x) - (h.b * a.y);
	dot t; //T is an intersection of lines h and b.
	t.x = (b.b * h.c - b.c * h.b)/(b.a * h.b - b.b * h.a);
	t.y = (b.a * h.c - b.c * h.a)/(b.b * h.a - b.a * h.b);
	return dtd(a, t); //Returns distance between dot A and its project on the line, T.
}

double dtls(dot x, dot a, dot b){ //Distance from Dot To Line Segment.
	double dist, xa, xb, ab;
	xa = dtd(x, a); //Three line segments.
	xb = dtd(x, b);
	ab = dtd(a, b);
	line l; //Line trough A and B.
	l.a = a.y - b.y;
	l.b = b.x - a.x;
	l.c = -l.a * a.x - l.b * a.y;
	if(pow(xa, 2) + pow(ab, 2) <= pow(xb, 2)) dist = dtd(x, a); //Pithagor's theorem at its finest.
	else{
		if(pow(xa, 2) >= pow(ab, 2) + pow(xb, 2)) dist = dtd(x, b); //Two times, actually.
		else dist = dtl(x, l);
	}
	return dist;
}

int main(){
	int n, n2, i, j; //n and n2 are numbers of vertices in first and second polygons, respectively. I and j are just usual cycle counters.
	FILE* in;

	in = fopen("in.txt", "r+");
	if(NULL == in){
		perror("File opening error!: "); //That's error output from stdlib.h
		return -1;
	}

	fscanf(in, "%i", &n);

	dot* polygon1 = (dot *) malloc(n * sizeof(dot)); //Creating first polygon
	if(NULL == polygon1) return -1;

	for(i = 0; i < n; i++){ //Filling first polygon
		fscanf(in, "%lf", &(polygon1+i)->x);
		fscanf(in, "%lf", &(polygon1+i)->y);
	}


	fscanf(in, "%i", &n2);

	dot* polygon2 = (dot *) malloc(n2 * sizeof(dot));
	if(NULL == polygon2) return -1; //Second polygon: memory and data.

	for(i = 0; i < n2; i++){
		fscanf(in, "%lf", &(polygon2+i)->x);
		fscanf(in, "%lf", &(polygon2+i)->y);
	}


	double mindist, d;
	mindist = 1.e45; //Placeholder for the biggest minimal distance.
	dot a, b, x;

	for(i = 0; i < n; i++){
		a = *(polygon1 + i); //Taking two adjacent vertices of first polygon...
		b = *(polygon1 + i + 1);
		if(i == n-1) b = *polygon1;
		for(j = 0; j < n2; j++){
			x = *(polygon2 + j); //And one from second.
			d = dtls(x, a, b); //Counting distance.
			if(d < mindist) mindist = d; //Smallest?
		}
	}

	for(i = 0; i < n; i++){
		x = *(polygon1 + i); //One vertice from the first polygon.
		for(j = 0; j < n2; j++){
			a = *(polygon2 + j); //Two from second one.
			b = *(polygon2 + j + 1);
			if(j == n2-1) b = *polygon2;
			d = dtls(x, a, b);
			if(d < mindist) mindist = d;
		}
	}

	if(1e45 == mindist) return 0; //If distance is bigger than THIS... I'm not gonna do it.

	printf("%.2lf\n", mindist);

	free(polygon1); //Freeing memory
	free(polygon2);

	return 1; //Return of main(), useful only for debuging and real projects
}
