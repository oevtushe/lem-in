#include "lem_in.h"

static void	print_path_helper(t_lmdata *data, t_pair *extra, int idx)
{
	if (((t_node*)data->adj[idx]->content)->name == ((t_node*)((t_list*)extra->fst)->content)->name)
	{
		ft_printf("%s", ((t_node*)data->adj[idx]->content)->name);
		return ;
	}
	else
		print_path_helper(data, extra, ((t_node*)data->adj[idx]->content)->p);
	ft_printf("->%s", ((t_node*)data->adj[idx]->content)->name);
}

void		print_path(t_lmdata *data, t_pair *extra)
{
	t_node	*end;

	end = (t_node*)((t_list*)extra->scd)->content; 
	if (!end->d)
	{
		ft_printf("There is no path between start and end !\nERROR\n");
		return ;
	}
	print_path_helper(data, extra, get_node_idx(data, ((t_node*)((t_list*)extra->scd)->content)->name));
	ft_putchar('\n');
}
