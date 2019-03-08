xo = 50;
        yo =50;
        radius=50;
        angle=0;
        %x = xo - radius * cosd(rad2deg(angle))
        %y = yo + radius * sind(rad2deg(angle))
%         cos=cosd(angle);
%         sin=sind(angle);
%         x = xo - radius * cosd(angle);
%         y = yo + radius * sind(angle);
       for angle=1:1:180
        x = xo-radius* cosd(angle)
        y= yo+radius*sind(angle)
        hold on
        plot(x,y,'-.b*')
       end
       