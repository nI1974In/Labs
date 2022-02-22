#!/usr/bin/bash awk

BEGIN {
    print "Город прибытия\t\tВремя вылета\tВремя прилета\tДлительность полёта"
}

{
    if (arrival == $1) {
	minutes = $5 - $3
	hour = $4 - $2
	if (minutes < 0) {
	    --hour
	    minutes = 60 + minutes
	}

	if (hour < 0) {
	    hour = hour + 24
	}

	if (minutes < 10) {
	    print $1 "\t\t   " $2 ":" $3 "\t   " $4 ":" $5 "\t   " hour ":0" minutes
	} else {
	    print $1 "\t\t   " $2 ":" $3 "\t   " $4 ":" $5 "\t   " hour ":" minutes
        }
    } else if (arrival == "") {
        minutes = $5 - $3
        hour = $4 - $2
        if (minutes < 0) {
            --hour
            minutes = 60 + minutes
        }

        if (hour < 0) {
            hour = hour + 24
        }

        if (minutes < 10) {
            print $1 "\t\t   " $2 ":" $3 "\t   " $4 ":" $5 "\t   " hour ":0" minutes
        } else {
            print $1 "\t\t   " $2 ":" $3 "\t   " $4 ":" $5 "\t   " hour ":" minutes
        }

    }

}
