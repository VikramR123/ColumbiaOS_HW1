#include <linux/module.h>
#include <linux/sched/task.h>

void print_tree(struct task_struct *t, int level)
{
	struct task_struct *child;
	struct list_head *list;
	char *spaces;

	//print lines
	if (level == 0) {
		spaces = "-- ";
	} else {
		int i;
		int num_spaces;
		spaces = "";
		num_spaces = 4 * min(level, 20);
		for (i=0; i<num_spaces; i++) {
			spaces = strcat(spaces, " ");
		}
		spaces = strcat(spaces, "\\_ ");
	}

	printk(KERN_INFO "%s[%d] %s\n", spaces, t->pid, t->comm);
	list_for_each(list, &t->children) {
		child = list_entry(list, struct task_struct, sibling);
		print_tree(child, level+1);
	}
}

int tasklist_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	//int num_spaces;
	//num_spaces = 4 * min(cur_level, 20);

	struct task_struct *p = &init_task;
	print_tree(p, 0);
	//printk(KERN_INFO "[%d] %s\n", p->pid, p->comm);

	return 0;
}

void tasklist_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}

module_init( tasklist_init );
module_exit( tasklist_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Tasklist Module");
MODULE_AUTHOR("SGG");
