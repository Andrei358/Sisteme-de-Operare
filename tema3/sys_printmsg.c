int 
sys_printmsg(struct proc *p, void *v, register_t *retval)
{
	struct sys_print_msg, *uap = v;
	
	char *kmsg = malloc(200, M_TEMP, M_WAITOK);
	copyinstr(SCARG(uap, msg), kmsg, 200, NULL);
	printf(kmsg);
	free(buf, M_TEMP, 200)
	return 0;
}