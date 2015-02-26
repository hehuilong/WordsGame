#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "grille.h"

#define X 8
#define Y 8
#define M 4
#define BUTTON_SIZE 25

typedef struct{
	gint numberRest;
	gboolean mark;
	gint y,x;
	GtkWidget* buttons[TAILLE_GRILLE_Y][TAILLE_GRILLE_X];
	GtkWidget* labels[NOMBRE_MOT];
	gboolean found[NOMBRE_MOT];
}Grille_GTK;

GtkWidget *window;
Grille_GTK g;
Grille grille;
GdkColor color;
GdkColor color_origi_button;
GdkColor color_origi_label;


void set_game();
void init_game();
gboolean on_click(GtkWidget*,GdkEventButton*,gpointer);
gint in_list(Mot);

void init_game(){
	
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Words Game");
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_exit),NULL);
	
	GtkWidget *vbox_l=gtk_vbox_new(TRUE,0);
	GtkWidget *vbox_r=gtk_vbox_new(FALSE,4);
	GtkWidget *hbox1=gtk_hbox_new(FALSE,15);
	GtkWidget *hbox2;
	GtkWidget *hbox_fill_right=gtk_hbox_new(FALSE,0);	
	
	gtk_box_pack_start(GTK_BOX(hbox1),vbox_l,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),vbox_r,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),hbox_fill_right,FALSE,FALSE,0);
	
	gint i,j;
	for(i=0;i<Y;i++){
		hbox2=gtk_hbox_new(TRUE,0);
		for(j=0;j<X;j++){
			g.buttons[i][j]=gtk_button_new_with_label("");
			gtk_widget_set_usize(g.buttons[i][j],BUTTON_SIZE,BUTTON_SIZE);
			gtk_object_set(GTK_OBJECT(g.buttons[i][j]),"can-focus",FALSE,NULL);
			gtk_signal_connect(GTK_OBJECT(g.buttons[i][j]),"button_press_event",GTK_SIGNAL_FUNC(on_click),GINT_TO_POINTER(i*X+j));
			gtk_box_pack_start(GTK_BOX(hbox2),g.buttons[i][j],FALSE,FALSE,0);
		}
		gtk_box_pack_start(GTK_BOX(vbox_l),hbox2,FALSE,FALSE,0);
	}
	
	for(i=0;i<M;i++){
		g.labels[i]=gtk_label_new("");
		gtk_box_pack_start(GTK_BOX(vbox_r),g.labels[i],FALSE,FALSE,0);
	}
	
	GtkWidget *button=gtk_button_new_with_label("RESET");
	gtk_box_pack_end(GTK_BOX(vbox_r),button,FALSE,FALSE,20);
	gtk_signal_connect(GTK_OBJECT(button),"button_press_event",GTK_SIGNAL_FUNC(set_game),NULL);

	gtk_container_add(GTK_CONTAINER(window),hbox1);
	
	gtk_widget_show_all(window);
}

void set_game(){
	
	g.numberRest=M;
	g.mark=FALSE;
	genererGrille(&grille,X,Y,M,"dict_e","ref_dict_e");
	gint i,j;
	for(i=0;i<M;i++){
		g.found[i]=FALSE;
		gtk_widget_modify_fg(g.labels[i], GTK_STATE_NORMAL, &color_origi_label);
	}
	for(i=0;i<Y;i++){
		for(j=0;j<X;j++){
			char a[2];
			a[0]=grille.tableau[i][j];
			a[1]='\0';
			gtk_button_set_label(GTK_BUTTON(g.buttons[i][j]),a);
			gtk_widget_modify_bg(g.buttons[i][j], GTK_STATE_NORMAL, &color_origi_button);
		}
	}
	for(i=0;i<M;i++){
		gtk_label_set_text(GTK_LABEL(g.labels[i]),grille.listeMots[i].mot);
	}
}

gboolean on_click(GtkWidget* widget,GdkEventButton* event,gpointer data){


	if(g.mark){
		gtk_widget_modify_bg(g.buttons[g.y][g.x], GTK_STATE_NORMAL, &color_origi_button);
	}
	
	color.red = randIntervalle(15000,50000);
	color.green = randIntervalle(15000,50000);
	color.blue = randIntervalle(15000,50000);
	
	gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
	
	gint index=GPOINTER_TO_INT(data);
	gint x,y;
	y=index/X;
	x=index%X;
	
	if(!g.mark){
		g.mark=TRUE;
		g.x=x;
		g.y=y;
		return TRUE;
	}
	
	if(x!=g.x && y!=g.y && (x-g.x)!=(y-g.y) && (x-g.x)!=-(y-g.y)){
		g.x=x;
		g.y=y;
		return TRUE;
	}
	
	gint dx,dy;
	dx=x==g.x?0:1;
	dx=x<g.x?-1:dx;
	dy=y==g.y?0:1;
	dy=y<g.y?-1:dy;
	gint px=g.x,py=g.y;
	
	Mot m;
	gint c=-1;
	while(!(px==x+dx && py==y+dy)){
		m[++c]=grille.tableau[py][px];
		px+=dx;
		py+=dy;
	}
	m[++c]='\0';
	
	Mot mrev;
	gint i;
	for(i=0;i<c;i++)mrev[i]=m[c-1-i];
	mrev[c]='\0';
	
	gint m_in=in_list(m);
	gint mrev_in=in_list(mrev);
	gint index_in_list=m_in==-1?mrev_in:m_in;

	if(index_in_list==-1){
		g.x=x;
		g.y=y;
		return TRUE;
	}
	
	g.mark=FALSE;

	px=g.x;py=g.y;
	while(!(px==x+dx && py==y+dy)){
		gtk_widget_modify_bg(g.buttons[py][px], GTK_STATE_NORMAL, &color);
		px+=dx;
		py+=dy;
	}
	
	gtk_widget_modify_fg(g.labels[index_in_list], GTK_STATE_NORMAL, &color);
	
	g.numberRest-=1;
	if(g.numberRest==0){
		GtkWidget *dialog;
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Congrat! You win!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		set_game();
	}
	
	return TRUE;
}

gint in_list(Mot m){
	gint i;
	for(i=0;i<grille.nombreMots;i++){
		if(g.found[i])continue;
		if(strcasecmp(m,grille.listeMots[i].mot)==0){
			g.found[i]=TRUE;
			return i;
		}
	}
	return -1;
}

int main(int argc, char *argv[]){
	
	color_origi_button.red = 55000;
	color_origi_button.green = 55000;
	color_origi_button.blue = 55000;
	
	color_origi_label.red = 10000;
	color_origi_label.green = 10000;
	color_origi_label.blue = 10000;
	
	srand(time(NULL));
	gtk_init(&argc,&argv);
	init_game();
	set_game();
	gtk_main();
	return EXIT_SUCCESS;
}
