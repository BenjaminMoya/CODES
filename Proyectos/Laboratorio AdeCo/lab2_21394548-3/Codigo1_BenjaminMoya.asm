.data
	 msg1: .asciiz "Ingrese el valor del angulo:  \n"
   	 msg2: .asciiz "Que operacion desea realizar?\n"
   	 msgseno: .asciiz "1)Seno\n"
   	 msgcoseno: .asciiz "2)Coseno\n"
   	 floatpoint: .asciiz "."  
   	 finalmsg: .asciiz "La estimacion es del resultado es de:" 
.text

				#Pedimos por consola el angulo y mostramos el numero asignado a la opcion
    li $v0, 4
    la $a0, msg1
    syscall		
    li $v0, 5
    syscall
    move $t0, $v0  		#Guardamos el angulo en $t0
    
    li $v0, 4
    la $a0, msg2
    syscall
    li $v0, 4
    la $a0, msgseno
    syscall
    li $v0, 4
    la $a0, msgcoseno
    syscall	
    			
    li $v0, 5
    syscall
    move $s0, $v0  		#Guardamos la opccion en $s0
    
    beq $s0,1,sin
    beq $s0,2,cos
    
	sin:
		li $t1,6 	#Factorial de 3
		li $t2,120	#Factorial de 5
		li $t3,5040	#Factorial de 7
	
		jal x3
		move $t7,$t5
		jal x5
		move $t8,$t5
		jal x7
		move $t9,$t5
	
				#Division del primer termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t7 	
        	move $s1,$t1  	
          	jal division
		move $t1,$s2     
        	move $t7,$s3   	
	
				#Division del segundo termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t8  	
        	move $s1,$t2  	
          	jal division
		move $t2,$s2    
        	move $t8,$s3  	
        
        			#Division del tercer termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t9   	
        	move $s1,$t3  	
		jal division
		move $t3,$s2   	
        	move $t9,$s3  	
        	   		#Realizamos la sumatoria de la serie con los primeros 4 terminos
        	sub $t1,$t0,$t1		
        	sub $t2,$t2,$t3
        	sub $t8,$t8,$t9
        	add $t1,$t1,$t2
        	add $t7,$t7,$t8
        	bge $zero ,$t7, sign
        	j result
	
	cos:
		li $t1,2	#Factorial de 2
		li $t2,24	#Factorial de 4
		li $t3,720	#Factorial de 6
		li $t4,40320	#Factorial de 8
	
		jal x2
		move $t6,$t5
		jal x4
		move $t7,$t5
		jal x6
		move $t8,$t5
		jal x8
		move $t9,$t5
	
				#Division del primer termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t6 	
        	move $s1,$t1  	
          	jal division
		move $t1,$s2    
        	move $t6,$s3   	
        
        			#Division del segundo termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t7 	
        	move $s1,$t2  	
          	jal division
		move $t2,$s2     
        	move $t7,$s3   
        
        			#Division del tercer termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t8 	
        	move $s1,$t3  	
          	jal division
		move $t3,$s2     
        	move $t8,$s3   	
        
        			#Division del cuarto termino donde guardamos la parte entera y la decimal por separado
		move $s0,$t9 	
        	move $s1,$t4  	
          	jal division
		move $t4,$s2     
        	move $t9,$s3   	
        
        			#Realizamos la sumatoria de la serie con los primeros 5 terminos
        	add $t1,$t1,$t2
        	add $t6,$t6,$t7	
        	add $t3,$t3,$t4
        	add $t8,$t8,$t9		
        	sub $t1,$t1,$t3
        	sub $t7,$t6,$t8
        	li $s1,1
        	sub $t1,$s1,$t1
        
	
	 	bge $zero ,$t7, sign
        	j result
        	
        result:
				    #Imprimimos en consola el mensaje del resultado
    		li $v0, 4           
    		la $a0, finalmsg    
    		syscall            
	    			    #Imprimimos la parte entera almacenada en $t2
    		move $a0, $t1       
    		li $v0, 1          
    		syscall             

    				    #Imprime el punto 
    		li $v0, 4           
    		la $a0, floatpoint     
    		syscall             

    				    #Imprime la parte decimal almacenada en $t3
    		move $a0, $t7       
    		li $v0, 1          
    		syscall             

    				    #Llamamos a terminar la ejecucion
    		li $v0, 10          
    		syscall             
     
#------------------------------------Subrutinas-----------------------------------# 
    		
    			            #Para operar las potencias usamos $s4 como contador, donde realizaremos en los loops, lo equivalente a la multiplicacion dependiendo del exponente
	x2:
    		li $s4, 1      	   
    		move $s1, $t0       
    		subi $s1, $s1, 1    
    		move $t5, $t0       #Aqui volvemos a inicializar el exponente pero en $t5 
	restart1:
    		move $s5, $s1       
    		move $s3, $t5       #Ajustamos el exponente para el ciclo
	loop1:
    		add $t5, $t5, $s3   #Realizamos la multiplicacion hasta que $s5 sea 0
    		sub $s5, $s5, 1     
    		bnez $s5, loop1     
   		subi $s4, $s4, 1    
    		beqz $s4, jump      #Si el contador del exponente es 0 retornamos sino por el flujo natural del programa volveremos a empezar
    		j restart1
    		
				    #Para todos los demas exponentes funciona de la misma manera
	x4:
		li $s4,3
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart2:
		move $s5, $s1
		move $s3,$t5
	loop2:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop2
		subi $s4,$s4,1
		beqz $s4,jump
		j restart2
		
	x6:
		li $s4,5
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart3:
		move $s5, $s1
		move $s3,$t5
	loop3:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop5
		subi $s4,$s4,1
		beqz $s4,jump
		j restart3
			
	x8:
		li $s4,7
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart4:
		move $s5, $s1
		move $s3,$t5
	loop4:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop4
		subi $s4,$s4,1
		beqz $s4,jump
		j restart4
	
	x3:
		li $s4,2
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart5:
		move $s5, $s1
		move $s3,$t5
	loop5:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop5
		subi $s4,$s4,1
		beqz $s4,jump
		j restart5
		
	x5:
		li $s4,4
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart6:
		move $s5, $s1
		move $s3,$t5
	loop6:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop6
		subi $s4,$s4,1
		beqz $s4,jump
		j restart6
		
	x7:
		li $s4,6
		move $s1,$t0
		subi $s1,$s1,1
		move $t5,$t0
	restart7:
		move $s5, $s1
		move $s3,$t5
	loop7:
		add $t5,$t5,$s3
		subi $s5,$s5,1
		bnez $s5,loop7
		subi $s4,$s4,1
		beqz $s4,jump
		j restart7
	
	division:
    		li $s2, 0				#Cargamos tanto el cociente como el residuo de la division en $s2 y $s3 respectivamnete
    		li $s3, 0  				
    							
		divideint:
    			li $s5, 0          		#Asignamos a $s5 como contador
    			li $s6, 0          		
    			li $s7, 2          		
    			bgt $s1,$s0,dividedec
		divideintloop:
    			sub $s0, $s0, $s1  		#Restamos nuestro resultado actual hasta obtener que el $s1 sea mayor que $s0
    			addi $s5, $s5, 1   		
    			bgt $s1,$s0,dividedec
    			j divideintloop
   
		dividedec:				
   			beqz $s0,dividefinal
    			li  $s4, 10
   		 	move $t5,$s0
   		 	multi:
     				add $s0,$s0,$t5
     				subi $s4,$s4,1
     				bnez $s4,multi
    			bgt $s1,$s0,dividedec
    		
		dividedecloop:
    			sub $s0, $s0, $s1  		# Para la parte decimal ocupamos la misma tecnica donde mediante el up nos aseguramos si hay residuo decimal o es exacto
    			addi $s6, $s6, 1   		
    			bgt $s1,$s0,up
    			j dividedecloop      		
    			up:
    				beqz $s7, dividefinal
    				li  $s4, 10
    				move $t5,$s6
     				multi2:
					add $s6,$s6,$t5
     					subi $s4,$s4,1
     					bnez $s4,multi2
    			subi $s7,$s7,1
    			j dividedec

		dividefinal:
    			move $s2, $s5      	 	#Asignamos la parte entera y la decimal a $s4 y $s5 respecctivamente
    			move $s3, $s6       		
    			j jump
    
	jump:
		jr $ra 					#Retorno
    
	sign:
		sub $t7,$zero,$t7
        	j result
