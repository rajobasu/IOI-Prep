[SUBTASK 1]
left
loop:
	right
	right
	pebble goToRight
	halt
	goToRight:
	get
	move
	right
	right
	pebble gotoleft
	halt 
	gotoleft:
	get
	move
jump loop

[SUBTASK 2]

right
loopoof:
	#this loop is to continue till we get a 0 in one of the cells
	#try extracting something from the 00 cell
	pebble cont1
	jump rektin00
	cont1:
	get
	right
	move
	put
	right
	right
	move
	right
	# we have displaced 1 unit from 00 
	move
	# now we try to do the same for 01
	pebble cont2
	jump rektin01
	cont2:
	get
	right
	move
	put
	right
	right
	move
	left

	move
	right
	right
jump loopoof

rektin00:
loop2:
	#note that i am facing right currently
	right


	move
	pebble isok
	right 
	right
	move
	halt
	isok:
	get
	right
	right
	move
	put
	right
	move
	put
	right
	move
	get
	right
	right
	move
	left
	move
	right
	right
jump loop2
halt


rektin01:
loop3:
	#note that i am facing right currently

	#loop7:
	#jump loop7

	loop4:
		put
		right
		move
		pebble isok2

		right
		right
		move
		get
		left
		move
		# now start picking those in 00 
		right
		right
		loop5:
			right
			move
			pebble isok3
				#halt
				right
				right
				move

				#get
				right

				move
				halt
			isok3:
			get
			right
			right
			move
			put
			#halt
			right
			#right
		jump loop5

		isok2:
		get
		right
		right
		move
		right
	jump loop4
jump loop3
halt

[SUBTASK 3]
right #orient
loop1:
	pebble gtp
	#this is the first time it has got the pebble
	jump sedd
	gtp:
	get
	move
	put
	jump nextloop
	sedd:
	move
jump loop1

nextloop:
	move
	pebble gotthepebble
	jump mehh
	gotthepebble:
	right
	right
	get
	move
	pebble ooof
	put
	jump mehh
	ooof:
	halt
	mehh:
jump nextloop

