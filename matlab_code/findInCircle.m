function position = findInCircle(display_image, scan_)
         data=zeros(length(scan_(:,1))-1);
         data(1,1)=0;
         data(length(scan_)-1,1)=0;
         for index = 2:1: length(scan_)
                data(index) = scan_(index - 1,1) - scan_(index,1);
         end
         left = [1,1];
         right = [1,1];
         
         for index =1:1: length(data)
                if data(index) > left(2)
                        left(2) = data(index);
                        left(1) = index;
                      
                        
                end
                if data(index) < right(2)
                        right(2) = data(index);
                        right(1) = index;
                end
         end
        leftx = scan_(left(1),2);
        lefty = scan_(left(1),3);
        lefti = left(1);
        rightx = scan_(right(1),2);
        righty = scan_(right(1),3);
        righti = right(1);
        x = round((rightx + leftx)/2);
        y= round((righty + lefty)/2);
        position = [x,y];
       
end