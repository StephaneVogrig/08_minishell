/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:24:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 14:58:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input_to_pipeline.h"
#include "debug.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define PURPLE "\033[38;5;135m"

void	test(char *str, t_env *env)
{
	int		exit_status;
	t_cmd_m	*pipeline;

	exit_status = 0;
	pipeline = input_to_pipeline(str, env, &exit_status);
	ft_printf(PURPLE);
	ft_printf("%s\n", str);
	ft_printf(RESET);
	print_pipeline(pipeline);
	pipeline_free(&pipeline);
}

int main(int argc, char **argv, char **envp)
{
	t_env_m	*env;
	(void)argc;
	(void)argv;

	env = env_dup(envp);
	test("", env);
	test("<in cat | cd >out", env);
	test("<<in>out dsjkf>>>\"\">out2 cat | < file cd >out", env);
	test("ab sdf sdf   \t  fdsfj   \t  sfd", env);
	test("s\"  a  \"fd sf'  a  'd  sds''fd  sfds\"\"dff \"\" '' ", env);
	test("$A$B$C$D", env);
	test("<< <<$A$B$C<<''$D", env);
	test("<< \"$VAR\" > out", env);
	test("<< \"$VAR\" | < in ls -l | cat -e >> out | cat -e > out", env);
	
	env_free(env);
	return (0);
}
