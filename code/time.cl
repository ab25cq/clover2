
time:ulong = System.time();

tm_sec:=0; 
tm_min:=0; 
tm_hour:=0; 
tm_mday:=0; 
tm_mon:=0; 
tm_year:=0; 
tm_wday:=0; 
tm_yday:=0; 
tm_isdst:=false; 
System.localtime(time, &tm_sec, &tm_min, &tm_hour, &tm_mday, &tm_mon, &tm_year, &tm_wday, &tm_yday, &tm_isdst);

printf("sec %d min %d hour %d mday %d mon %d year %d\n", array { tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year });
