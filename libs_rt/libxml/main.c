# include <stdio.h>
# include <libxml.h>

int main(int argc, char **argv)
{
	t_xml *x, *t;
	if (argc != 2)
		return (0);
	x = xml_init(argv[1]);
	if (xml_parse(x) == -1)
		printf("xml: -1\n");
	t = x;
	printf("\n*********Output*********\n");
	while (x && x->tags)
	{
		printf("  [%s]\n", x->tags->name);
		while (x->tags->attr)
		{
			printf("\t{%s \"%s\"}\n", x->tags->attr->name, x->tags->attr->value);
			x->tags->attr = x->tags->attr->next;
		}
		x->tags = x->tags->next;
	}
	x = t;
	xml_close(x);
	return (0);
}
