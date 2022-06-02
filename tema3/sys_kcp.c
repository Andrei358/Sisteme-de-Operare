int 
sys_kcp(struct proc *p, void *v, register_t *retval)
{
	struct sys_kcp_arg, *uap = v;
	
	size_t nbyte = SCARG(uap, nbyte);
	void *kbuf = malloc(nbyte, M_TEMP, M_WAITOK);
	int ret;
	
	ret = copyin(SCARG(uap, from), kbuf, nbyte);
	if(ret != 0){
		free(kbuf, M_TEMP, nbyte);
		*retval=-1;
		return -1;
	}
	
	ret = copyout(kbuf, SCARG(uap, to), nbyte);
	free(kbuf, M_TEMP, nbyte);
	
	if(ret != 0){
		*retval=-1;
		return -1;
	}
	
	*retval = nbyte;
	return 0;
}