/* ʱ�����ʱ timer.c */
/* ����timer���򼴿ɿ�ʼ�򵥵ļ�ʱ */
#include <gtk/gtk.h>//gtkͷ�ļ�
#include <time.h>//ʱ��ͷ�ļ�
static GtkWidget *clocker;

static GtkWidget *our_timer;
static GtkWidget *button_begin; //��ʼ��ť
static GtkWidget *button_end; //������ť
gint timer_id;//ʱ�˱��
gint hour = 0;//ʱ
gint min = 0;//��
gint sec = 0;//��
void clock_begin()
{
	//ʱ�ӿ�ʼ
	time_t now ;
	struct tm *l_time;
	gchar buf[100];
	now = time((time_t *)NULL);
	l_time = localtime(&now); //ȡ����ʱ��
	sprintf(buf,"%d:%d:%d",l_time->tm_hour,l_time->tm_min,l_time->tm_sec);//��ӡ��ǰʱ��
	gtk_label_set_text(GTK_LABEL(clocker),buf);
}
void timer_add()
{
	//����Ϊ��λ��ʱ
	gchar buf[100];
	sec++;
	if(sec == 60)	//60���һ��
	{
		min++;
		if(min == 60) //60�ּ�һСʱ
		{
			hour++;
			min = 0;
		}
		sec = 0;
	}
	sprintf(buf,"%d : %d : %d",hour,min,sec);//��ӡʱ��
	gtk_label_set_text(GTK_LABEL(our_timer),buf);
}
void timer_begin()
{
	//��ʼ��ʱ
	gtk_widget_set_sensitive(button_begin,FALSE);
	gtk_widget_set_sensitive(button_end,TRUE);
	timer_id = gtk_timeout_add(1000,(GtkFunction)timer_add,NULL);
}
void timer_end()
{
	//������ʱ
	gtk_widget_set_sensitive(button_begin,TRUE);
	gtk_widget_set_sensitive(button_end,FALSE);
	gtk_timeout_remove(timer_id);
}
int main ( int argc , char* argv[])//������
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *sep;
	GtkWidget *label;
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",
	G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"ʱ�����ʱ");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	label = gtk_label_new("�򵥵�����ʱ��:");
	gtk_box_pack_start(GTK_BOX(hbox),label,TRUE,TRUE,5);
	clocker = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(hbox),clocker,TRUE,TRUE,5);
	gtk_timeout_add(1000,(GtkFunction)clock_begin,NULL);
	sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	label = gtk_label_new("�򵥵ļ�ʱ��:");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
	our_timer = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(hbox),our_timer,FALSE,FALSE,5);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);
	button_begin = gtk_button_new_with_label("��ʼ");
	g_signal_connect(G_OBJECT(button_begin),"clicked",
	G_CALLBACK(timer_begin),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button_begin,TRUE,TRUE,5);
	button_end = gtk_button_new_with_label("ֹͣ");
	gtk_widget_set_sensitive(button_end,FALSE);
	g_signal_connect(G_OBJECT(button_end),"clicked",
	G_CALLBACK(timer_end),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button_end,TRUE,TRUE,5);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}