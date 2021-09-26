#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>

/*
 * Undefine commonly used macros -- DO NOT MODIFY
 * Please also do not use other macros and functions defined in <linux/list.h>,
 * such as INIT_LIST_HEAD, list_add, list_add_tail, list_del, list_empty,
 * or any of the internal helper functions beginning with __.
 */
#undef LIST_HEAD
#undef LIST_HEAD_INIT
#undef list_entry
#undef list_for_each_entry
#undef list_for_each_entry_safe
#undef container_of
#undef offsetof
#undef READ_ONCE
#undef WRITE_ONCE

struct pokemon {
	char name[32];
	int dex_no;
	struct list_head list;
};

void print_pokemon(struct pokemon *p)
{
	printk(KERN_INFO "%s: National Dex No. #%d\n", p->name, p->dex_no);
}

/* TODO: declare a single static struct list_head, named pokedex */
static struct list_head pokedex = { &(pokedex), &(pokedex) };

void add_pokemon(char *name, int dex_no)
{
	/* TODO: write your code here */
	struct pokemon *new;

	new = kmalloc(sizeof(*new), GFP_KERNEL);
	strcpy(new->name, name);
	new->dex_no = dex_no;
	struct list_head tmp = { &(tmp), &(tmp) };
	//new->list = { &(new->list), &(new->list) };
	new->list = tmp;

	// List add
	struct list_head *newlist = &new->list;
	struct list_head *prev = &pokedex;
	struct list_head *next = (&pokedex)->next;

	next->prev = newlist;
	newlist->next = next;
	newlist->prev = prev;
	prev->next = newlist;
}

void print_pokedex(void)
{
	/* TODO: write your code here, using print_pokemon() */
	struct list_head *p;
	struct pokemon *pok;
	
	for (p = (&pokedex)->next; p != (&pokedex); p = p->next) {
		const typeof( ((struct pokemon *)0)->list ) *__mptr = (p);
		pok = (struct pokemon *) ( (char *)__mptr - ((size_t) &(((struct pokemon *)0)->list)) );
		print_pokemon(pok);
		//pok = list_entry(p, struct pokemon, list);
	}
}

void delete_pokedex(void)
{
	/* TODO: write your code here */
	struct pokemon *pos, *q;

	//
	const typeof( ((struct pokemon *)0)->list ) *__mptr = ((&pokedex)->next);
	pos = (struct pokemon *) ( (char *)__mptr - ((size_t) &(((struct pokemon *)0)->list)) );

	//const typeof( ((struct pokemon *)0)->list ) *__mmptr = ((pos)->list.next);
	q = (struct pokemon *) ( (char *)__mptr - ((size_t) &(((struct pokemon *)0)->list)) );

	//for (pos, q; &pos->list != &pokedex; pos=q, q = (struct pokemon *) ( (char *)__mptr - ((size_t) &(((struct pokemon *)0)->list)) )) {
		//
		//printk(KERN_INFO "Inner Loop Test");
	//}

	//for (pos = list_first_entry(head, typeof(*pos), member),	\
	//	n = list_next_entry(pos, member);			\
	//     !list_entry_is_head(pos, head, member); 			\
	//     pos = n, n = list_next_entry(n, member))
}

int pokedex_nom_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	add_pokemon("Porygon-Z", 474);
	add_pokemon("Exeggutor", 103);
	add_pokemon("Poliwhirl", 61);
	add_pokemon("Infernape", 392);

	print_pokedex();

	return 0;
}

void pokedex_nom_exit(void)
{
	printk(KERN_INFO "Removing Module\n");

	print_pokedex();

	delete_pokedex();
}

module_init( pokedex_nom_init );
module_exit( pokedex_nom_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A handy Pokedex module, without list macros");
MODULE_AUTHOR("SGG");
