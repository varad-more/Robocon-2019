function coordinateFromPoint(origin, angle, radius)
        xo = origin(0)
        yo = origin(0)
        x = xo - radius * cos(degtorad(angle))
        y = yo + radius * sin(degtorad(angle))
 
end