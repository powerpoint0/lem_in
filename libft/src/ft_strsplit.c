/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:59:21 by dfigg             #+#    #+#             */
/*   Updated: 2020/02/18 22:15:32 by clouise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				**ft_free_all(char **new, size_t i)
{
	while (i)
		ft_strdel(&new[i--]);
	ft_strdel(new);
	return (NULL);
}

static size_t			ft_num_words(char const *s, char c)
{
	size_t				i;
	size_t				word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] && s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static unsigned int		ft_word_l(char *s, char c)
{
	unsigned int		start;
	unsigned int		empty;

	start = 0;
	empty = 0;
	while (s[start])
	{
		if (s[start] == c)
			empty++;
		if (s[start] != c && (s[start + 1] == c || s[start + 1] == '\0'))
			return (start + 1 - empty);
		start++;
	}
	return (start - empty + 1);
}

static char				*find_next_word(char *s, char c, size_t i)
{
	size_t				leng;
	size_t				start;

	start = 0;
	leng = ft_strlen(s);
	if (i == 0 && s[start] != c)
		return (&s[start]);
	while (start < leng && s[start] != c)
		start++;
	while (s[start] == c && s[start])
	{
		if (s[start] == c && (s[start + 1] != c && s[start + 1] != '\0'))
			return (&s[start + 1]);
		start++;
	}
	return (0);
}

char					**ft_strsplit(char const *s, char c)
{
	char				**new;
	size_t				word;
	char				*s1;
	char				*s_found;
	size_t				i;

	if (!(s) || !(s1 = ft_strdup(s)) || !(c))
		return (NULL);
	s_found = s1;
	word = ft_num_words(s, c);
	if (!(new = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	i = 0;
	while (i < word && new != NULL)
	{
		s_found = find_next_word(s_found, c, i);
		if (!(new[i++] = ft_strsub(s, s_found - s1, ft_word_l(s_found, c))))
			return (ft_free_all(new, i - 1));
	}
	new[word] = (void *)0;
	return (new);
}
