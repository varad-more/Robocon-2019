img = snapshot(cam);
    gray=rgb2gray(img);
    intImage = integralImage(gray);
    avgH = integralKernel([1 1 7 7], 1/49);
    J = integralFilter(intImage, avgH);
    blur = uint8(J);
    threshold = [0.3 0.6];
    edged = edge(blur,'Canny',threshold);
    edged =uint8(edged);
    %subplot(2,1,2);
    imshow(edged)