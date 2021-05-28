# logic-circuit-calculator

#### this is a calculator for solve all logic circuit problems

#### in input.txt file:
  - you can make your symbol for calculate:
     operation:
     * and
     + or
     ~ not
     @ xor
  - you can make your values name like this:
  
    value:
    a1,a2,a3,a4,a5,a6
    
  - you can make your functions like this:
  
    function:
    o1=(~a1+~a2)@~a3
    o2=(a1@a4)+a2*(a5+(a3@a4))
    o3=(o1*o2)+a4
    o4=(o1+~o2)@a3
    o5=(a6+~a6)*(((~a5*((a4@~a1)*~a2))+(a5*((a4@~a1)*a2))))
    o6=(a6+o1)*(a5+a4+a6)
    o7=(o1*o2)+a4
    o8=(o1+o2@o3*o4+o5+o6@o7)
    o9=(~a1+~a2)@~a3+(a6+o1)*(a5+a4+a6)
    o10=(o1*o2)+a2*(~a1+~a2)
    o11=(~a1+~a2)@~a3
    o12=(a1@a4)+a2*(a5+(a3@a4))
    o13=(o1+o2@o3*o4+o5+o6@o7)
    o14=(a1@a4)+a2*(a5+(a3@a4))
    
    
    - full example for input file:
        operation:
        * and
        + or
        ~ not
        @ xor

        value:
        a1,a2,a3,a4,a5,a6

        function:
        o1=(~a1+~a2)@~a3
        o2=(a1@a4)+a2*(a5+(a3@a4))
    
    ## result is :
    ![alt text]()
      
    
