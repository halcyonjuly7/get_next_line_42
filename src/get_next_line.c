//
// Created by Halcyon abrah Ramirez on 4/7/18.
//

#include "get_next_line.h"
# include <unistd.h>
#include <libft.h>



void arr_insert(t_arr *arr, char new_char)
{
    if(arr->size == arr->contents)
        arr_resize(arr, arr->size * 2);
    arr->buffer[arr->contents] = new_char;
    arr->contents++;


}

void arr_resize(t_arr *arr, int new_size)
{
    int index;
    char *new_str;

    index = 0;
    new_str = ft_strnew(new_size);

    while(arr->buffer[index])
	{
		new_str[index] = arr->buffer[index];
		index++;
	}
    new_str[index] = '\0';
    ft_memdel((void *)&arr->buffer);
	arr->buffer = new_str;

}



int get_next_line(const int fd, char **line)
{
    char    *buffer;
    t_arr   local_buffer;
    int     index;
    int     cache_ind;
    static  t_arr *cache;


    if(!cache || !cache->buffer)
    {
		cache = malloc(sizeof(t_arr));
        cache->buffer = ft_strnew(BUFF_SIZE);
		if (!cache->buffer)
			return (0);
        cache->size = BUFF_SIZE;
        cache->contents = 0;
    }
    local_buffer.buffer = ft_strnew(BUFF_SIZE);
	if (!local_buffer.buffer)
		return (0);
	local_buffer.size = BUFF_SIZE;
	local_buffer.contents = 0;
    buffer = ft_strnew(BUFF_SIZE);
	if (!buffer)
		return (0);
    if (ft_strchr(cache->buffer, '\n'))
    {
        cache_ind = 0;
        while(cache->buffer[cache_ind] != '\n')
            cache_ind++;
        ft_strncpy(*line, cache->buffer, cache_ind);
        while(*cache->buffer != '\n')
            cache->buffer++;
		cache->buffer++;
        return (1);
    }
    while (read(fd, buffer, BUFF_SIZE))
    {
        index = 0;
        while (buffer[index])
        {
            if (buffer[index] == '\n')
            {
				index++;
				local_buffer.buffer[local_buffer.contents] = '\0';
                if (cache->buffer[0] != '\0')
                {
                    ft_strcpy(*line, ft_strjoin(cache->buffer, local_buffer.buffer));
					ft_strclr(cache->buffer);
					cache->contents = 0;
                }
				else
					ft_strcpy(*line, local_buffer.buffer);
                while (buffer[index])
					arr_insert(cache, buffer[index++]);
				ft_strdel(&local_buffer.buffer);
				ft_strdel(&buffer);
				return (1);
            }
            else
                arr_insert(&local_buffer, buffer[index]);
			index++;
        }
		ft_strclr(buffer);
    }
	ft_strdel(&local_buffer.buffer);
	ft_strdel(&cache->buffer);
	ft_memdel((void *)&cache);
    return (0);
}

