#shader vertex

void main(void){
    gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
}



#shader fragment

void main(void){
    gl_FragColor = vec4(1.0, 0.0, 1.0, 0.9);
}
