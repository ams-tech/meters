
/* Make sure our externs are defined */
#ifndef NUM_METERS
	#error "The number of meters (NUM_METERS) must be defined at compile time"
#endif

#ifndef METER_INIT_STR
	#error "The device initalizer (METER_INIT_STR) must be defined at compile time"
#endif

#ifndef METER_EXTERN_STR
	#error "The device externs (METER_EXTERN_STR) must be defined at compile time"
#endif

