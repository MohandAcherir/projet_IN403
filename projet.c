#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct noeud noeud;
typedef struct list list;

struct noeud{
    list* voisin;
    int distance;
    int vu;
    struct noeud* Table[100];
    int number;
    struct noeud* parent;
};

struct list{
    noeud* n;
    int weight;
    struct list* next;
};

noeud* get_root(noeud* u);

void append(list* l, noeud *N, int w){
	list* curr = l;

	while(curr->n != NULL){
		curr = curr->next;
	}

	curr->next = (list*)malloc(sizeof(list));
	curr->n = N;
	curr->weight = w;
	curr->next->next = NULL;
	curr->next->n = NULL;
}

void init_T1(noeud *T){
	int weight;

	for(int i = 0 ; i < 10 ; i++){
        	T[i].distance = 1000000; //+infini 
		T[i].voisin = (list*)malloc(sizeof(list));
		T[i].vu = 0;
		T[i].number = i;
		T[i].parent = NULL;
		T[i].Table;
		T[i].voisin->n = NULL;
		T[i].voisin->next = NULL;
	}

	for(int i = 0 ; i < 10 ; i++){
        	for(int j = i+1 ; j < 10 ; j++){
            		if((((int)rand())%100)+1 <= 75){
                		weight = rand()%6 + 5;
                		append(T[i].voisin, T+j, weight);
				append(T[j].voisin, T+i, weight);
            		}
        	}
    	}
}

void init_T2(noeud *T, noeud* T1){
	int index, index1 = -1;
	int w, k;

	for(int i = 0 ; i < 20 ; i++){
        	T[i].distance = 1000000;
		T[i].vu = 0;
		T[i].number = i+10;
		T[i].voisin = (list*)malloc(sizeof(list));
		T[i].voisin->n = NULL;
		T[i].parent = NULL;
		T[i].Table;
		T[i].voisin->next = NULL;
	}

	for(int i = 0 ; i < 20 ; i++){
        	w = (rand()%11)+10;
        
        	for(int k = rand()%2 + 1 ; k > 0 ; k--){
            		while((index = rand()%10) == index1);

            		append(T[i].voisin, T1+index, w);
			append(T1[index].voisin, T+i, w);

			index1 = index;
        	}
        
        	k = (rand()%2 == 0) ? 2 : 3;

		index1 = -1;

        	for(k ; k > 0 ; k--){
            		while((index = rand()%20) == index1);

            		append(T[i].voisin, T+index, w);
			append(T[index].voisin, T+i, w);

			index1 = index;
        	}
    	}
}

void init_T3(noeud *T, noeud *T2){
    	int index, index1;
	int w;

	for(int i = 0 ; i < 70 ; i++){
        	T[i].distance = 1000000;
		T[i].vu = 0;
		T[i].number = i+30;
		T[i].voisin = (list*)malloc(sizeof(list));
		T[i].parent = NULL;
		T[i].Table;
		T[i].voisin->n = NULL;
		T[i].voisin->next = NULL;
	}

	for(int i = 0 ; i < 70 ; i++){
        	index = rand()%20;

        	w = (rand()%(50 - 15 + 1)) + 15; //flemme
        	append(T[i].voisin, T2+index, w);
		append(T2[index].voisin, T+i, w);

		index1 = index;

        	while((index = rand()%20) == index1);

        	w = (rand()%(50 - 15 + 1)) + 15; //flemme
        	append(T[i].voisin, T2+index, w);
		append(T2[index].voisin, T+i, w);

        	index = (rand()%(70-i)) + i;

        	w = (rand()%(50 - 15 + 1)) + 15;
       	 	append(T[i].voisin, T+index, w);
		append(T[index].voisin, T+i, w);
    	}
}

void free_list(list* l){
	list* tmp;

	while(l){
		tmp = l;
		l = l->next;
		free(tmp);
	}
}

void free_graph(noeud* T1, noeud* T2, noeud* T3){
	for(int i = 0 ; i < 70 ; i++){
		if(i < 10){
			free_list(T1[i].voisin);
		}	
		if(i < 20){
			free_list(T2[i].voisin);
		}	
		if(i < 70){
			free_list(T3[i].voisin);
		}	
	}
}	

void DFS(noeud* s){
	s->vu = 1;
	//printf("node number %d is visited !\n", s->number);
	list* curr = s->voisin;
	
	while(curr){
		if(curr->n && (curr->n->vu == 0))
			DFS(curr->n);

		curr = curr->next;
	}
}

int is_connected(noeud* T1, noeud* T2, noeud* T3){
	for(int i = 0 ; i < 70 ; i++){
		if(i < 10 && (T1[i].vu == 0)){
			return 0;
		}
		if(i < 20 && (T2[i].vu == 0)){
			return 0;
		}
		if(T3[i].vu == 0){
			return 0;
		}
	}
	return 1;
}

void initialize(noeud* T1, noeud* T2, noeud* T3){
	for(int i = 0 ; i < 70 ; i++){
		if(i < 10){
			T1[i].vu = 0;
			T1[i].parent = NULL;
			T1[i].distance = 100000;
		}
		if(i < 20){
			T2[i].vu = 0;
			T2[i].parent = NULL;
			T2[i].distance = 100000;
		}
		T3[i].vu = 0;
		T3[i].parent = NULL;
		T3[i].distance = 100000;
	}
}

int w(noeud* u, noeud* v){
	list* l = u->voisin;
	int w = -1;
	
	while(l && l->n != v){
		l = l->next;
	}

	if(l && (l->n == v)){
		w = l->weight;
	}

	return w;
}

noeud* get_min(noeud* T1, noeud* T2, noeud* T3){
	int min = 1000000;
	noeud* n = NULL;

	for(int i = 0 ; i < 70 ; i++){
		if(i < 10){
			if((T1[i].vu == 0) && (T1[i].distance < min)){
				min = T1[i].distance;
				n = T1+i;
			}
		}
		if(i < 20){
			if((T2[i].vu == 0) && (T2[i].distance < min)){
				min = T2[i].distance;
				n = T2+i;
			}
		}
		if((T3[i].vu == 0) && (T3[i].distance < min)){
			min = T3[i].distance;
			n = T3+i;
		}
	}

	return n; 
}

int OK(noeud* T1, noeud* T2, noeud* T3, noeud* s){
	for(int i = 0 ; i < 10 ; i++){
		if((T1+i != s) && get_root(T1+i) != s)
			return 0;
	}
	for(int i = 0 ; i < 20 ; i++){
		if((T2+i != s) && get_root(T2+i) != s)
			return 0;
	}
	for(int i = 0 ; i < 70 ; i++){
		if((T3+i != s) && get_root(T3+i) != s)
			return 0;
	}
	return 1;
}

int Dijkstra(noeud* T1, noeud* T2, noeud* T3, noeud* s){
	if(s == NULL)
		return 1;
	
	initialize(T1, T2, T3);
	//printf("%d\n", s->number);
	s->distance = 0;
	s->vu = 1;
	s->parent = NULL;

	noeud* curr = s;

	list* k = NULL;

	while(curr != NULL){
		curr->vu = 1;
		k = curr->voisin;

		while(k->n){
			if(k->n->distance > (curr->distance + w(curr, k->n))){
				k->n->distance  = curr->distance + w(curr, k->n);
				k->n->parent = curr;
			}
			k = k->next;
		}
		//printf("curr is %d : %d", curr->number, curr->distance);
		curr = get_min(T1, T2, T3);
	}

	//printf("----->%d\n", OK(T1, T2, T3, s));

	return 0;
}

int is_ancestor(noeud* u, noeud* v){
	noeud* curr = u->parent;
	int found = 0;

	while(curr && !found){
		if(curr == v){
			found = 1;
		}
		else{
			curr = curr->parent;
		}	
	}

	return found;
}

noeud* get_common(noeud* u, noeud* v){
	noeud* curr = u;

	while(!is_ancestor(curr, v)){
		curr = curr->parent;
	}
	return curr;
}

void set(noeud* node, noeud* T1, noeud* T2, noeud* T3){
	int d = -1, dd, done = 0;
	list* k = NULL;

	//if(node == T1+1) printf("My parent is %d\n", node->parent->number);
	
	for(int i = 0 ; i < 70 ; i++){
		if(i < 10 && (T1+i != node)){
			done = 0;
			k = node->voisin;

			/*if(is_ancestor(T1+i, node) == 1)
			{*/
				while(k->n && !done){
					if(k->n->parent == node && (is_ancestor(T1+i, k->n) || T1+i == k->n)){
						done = 1;
					}
					else{
						k = k->next;
					}
				}

				
				node->Table[T1[i].number] = k->n;
		

		}
		
		if(i < 20 && (T2+i != node)){
		
        	done = 0;
			k = node->voisin;

			while(k && k->n && !done){
				if(k->n->parent == node && (is_ancestor(T2+i, k->n) || T2+i == k->n)){
					done = 1;
				}
					else{
						k = k->next;
					}
				}
				node->Table[T2[i].number] = k->n;
				
		}	

		if(i < 70 && (T3+i != node)){
			
            done = 0;
			k = node->voisin;

				d = abs(node->distance - T3[i].distance);
				
				while(k && k->n && !done){
					if(k->n->parent == node && (is_ancestor(T3+i, k->n) || T3+i == k->n)){
						done = 1;
					}
					else{
						k = k->next;
					}
				}

				
				node->Table[T3[i].number] = k->n;
		}
	}
	node->Table[node->number] = node;
}

void init_Table(noeud* T1, noeud* T2, noeud* T3){
	for(int i = 0 ; i < 10 ; i++){
		Dijkstra(T1, T2, T3, T1+i);
		set(T1+i, T1, T2, T3);
	}

	for(int i = 0 ; i < 20 ; i++){
		Dijkstra(T1, T2, T3, T2+i);
		set(T2+i, T1, T2, T3);
	}

	for(int i = 0 ; i < 70 ; i++){
		Dijkstra(T1, T2, T3, T3+i);
		set(T3+i, T1, T2, T3);
	}
}

noeud* get_root(noeud* u){
	while(u->parent){
		u = u->parent;
	}
	return u;
}

void get_chemin(noeud* u, int dest){

	noeud* v;
	int done = 0;
	int i = 0;

	v = u;

	while(!done){

		if(i)printf("->");
		
		i++;
		printf("%d", v->number);
		if(v->number == dest){
			done = 1;
		}
		else{
		v = v->Table[dest];
		}
		
	}printf("\n");

}

void ppath(noeud* u, noeud* v){
	noeud* pass = u;
	int i = 0;

	while(pass != v){
		if(i > 0){
			printf("-->");
		}
		i++;

		printf("U(%d)[%d]:%d", pass->number, v->number, pass->Table[v->number]->number);
		
		pass = pass->Table[v->number];
	}
	printf("\n");
}

int main(){
	
	int bool = 1;
	int done = 0;

	noeud T1[10];
	noeud T2[20];
	noeud T3[70];
	
	srand(time(NULL));

	while(1){
		
        init_T1(T1);
		init_T2(T2, T1);
		init_T3(T3, T2);

		DFS(T2+9);

		if(is_connected(T1, T2, T3)){
			break;
		}
		else{
			free_graph(T1, T2, T3);
		}
	}	
	
	init_Table(T1, T2, T3);

	while(bool){
		printf("\033[H\033[2J");
		printf("\n\t### Trouvez le plus court chemin entre deux noeuds de 0 à 99 ###\n");
		int Emetteur;
		int Destinataire; 

			printf("\n\tEntrez le noeud Emetteur = ");
			scanf("%d", &Emetteur);

			printf("\n\tEntrez le noeud Destinataire = ");
			scanf("%d",&Destinataire);

		if(Emetteur < 10){                  
			
			printf("\n\tLe plus court chemin de %d à %d est : ", Emetteur, Destinataire);
			get_chemin(T1+Emetteur, Destinataire);
			

		}else if((Emetteur < 20) && (Emetteur > 9)){
			
			printf("\n\tLe plus court chemin de %d à %d est : ", Emetteur, Destinataire);
			get_chemin(T2+(Emetteur-10), Destinataire);
			

		}else{
			
			printf("\n\tLe plus court chemin de %d à %d est : ", Emetteur, Destinataire);
			get_chemin(T3+(Emetteur-30), Destinataire);
			
		}
		
		printf("\n");
		printf("\n\tTapez 1 pour quittez 0 pour continuer : ");
		int choix;
		scanf("%d", &choix);
		if(choix)
		bool = 0;
	}
	free_graph(T1, T2, T3);

	
	
	
	return 0;
}




