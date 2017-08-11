#ifdef __cplusplus
extern "C" {
#endif

int FORK_RET_CODE = 12;
int EXECVP_RET_CODE = 0;
int KILL_RET_CODE = 0;

int __wrap_fork()
{
	return(FORK_RET_CODE);
}

int __wrap_execvp(const char *file, char *const argv[])
{
	return(EXECVP_RET_CODE);
}

int __wrap_kill(int pid, int signal)
{
	return(KILL_RET_CODE);
}
