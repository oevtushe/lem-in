#include "lem_in.h"

static void	save_path_helper(t_lmdata *data, t_pair *extra, int idx, t_list **ts)
{
	t_list *n;
	t_path *p;
	if (((t_node*)data->adj[idx]->content)->name == ((t_node*)((t_list*)extra->fst)->content)->name)
	{
		*ts = ft_lstnew(&idx, sizeof(int));
		return ;
	}
	else
		save_path_helper(data, extra, ((t_node*)data->adj[idx]->content)->p, ts);
	n = ft_lstnew(&idx, sizeof(int));
	ft_lstappend(ts, n);
}

void		save_path(t_lmdata *data, t_pair *extra, t_list **ts)
{
	t_node	*end;

	end = (t_node*)((t_list*)extra->scd)->content; 
	if (!end->d)
	{
		ft_printf("There is no path between start and end !\nERROR\n");
		return ;
	}
	save_path_helper(data, extra, get_node_idx(data, ((t_node*)((t_list*)extra->scd)->content)->name), ts);
}
