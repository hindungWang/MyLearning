/* 时钟与计时 timer.c */
/* 运行timer程序即可开始简单的计时 */
#include <gtk/gtk.h>//gtk头文件
#include <time.h>//时间头文件
static GtkWidget *clocker;

static GtkWidget *our_timer;
static GtkWidget *button_begin; //开始按钮
static GtkWidget *button_end; //结束按钮
gint timer_id;//时钏标记
gint hour = 0;//时
gint min = 0;//分
gint sec = 0;//秒
void clock_begin()
{
	//时钟开始
	time_t now ;
	struct tm *l_time;
	gchar buf[100];
	now = time((time_t *)NULL);
	l_time = localtime(&now); //取本地时间
	sprintf(buf,"%d:%d:%d",l_time->tm_hour,l_time->tm_min,l_time->tm_sec);//打印当前时间
	gtk_label_set_text(GTK_LABEL(clocker),buf);
}
void timer_add()
{
	//以秒为单位计时
	gchar buf[100];
	sec++;
	if(sec == 60)	//60秒加一分
	{
		min++;
		if(min == 60) //60分加一小时
		{
			hour++;
			min = 0;
		}
		sec = 0;
	}
	sprintf(buf,"%d : %d : %d",hour,min,sec);//打印时间
	gtk_label_set_text(GTK_LABEL(our_timer),buf);
}
void timer_begin()
{
	//开始计时
	gtk_widget_set_sensitive(button_begin,FALSE);
	gtk_widget_set_sensitive(button_end,TRUE);
	timer_id = gtk_timeout_add(1000,(GtkFunction)timer_add,NULL);
}
void timer_end()
{
	//结束计时
	gtk_widget_set_sensitive(button_begin,TRUE);
	gtk_widget_set_sensitive(button_end,FALSE);
	gtk_timeout_remove(timer_id);
}
int main ( int argc , char* argv[])//主函数
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
	gtk_window_set_title(GTK_WINDOW(window),"时钟与计时");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	label = gtk_label_new("简单的数字时钟:");
	gtk_box_pack_start(GTK_BOX(hbox),label,TRUE,TRUE,5);
	clocker = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(hbox),clocker,TRUE,TRUE,5);
	gtk_timeout_add(1000,(GtkFunction)clock_begin,NULL);
	sep = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	label = gtk_label_new("简单的计时器:");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,5);
	our_timer = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(hbox),our_timer,FALSE,FALSE,5);
	hbox = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);
	button_begin = gtk_button_new_with_label("开始");
	g_signal_connect(G_OBJECT(button_begin),"clicked",
	G_CALLBACK(timer_begin),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button_begin,TRUE,TRUE,5);
	button_end = gtk_button_new_with_label("停止");
	gtk_widget_set_sensitive(button_end,FALSE);
	g_signal_connect(G_OBJECT(button_end),"clicked",
	G_CALLBACK(timer_end),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button_end,TRUE,TRUE,5);
	gtk_widget_show_all(window);
	gtk_main();
	return FALSE;
}