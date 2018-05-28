#
# Regular cron jobs for the clover2 package
#
0 4	* * *	root	[ -x /usr/bin/clover2_maintenance ] && /usr/bin/clover2_maintenance
