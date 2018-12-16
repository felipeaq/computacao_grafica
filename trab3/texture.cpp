GLuint LoadTexture2( const char * filename, int width, int height )
{

    /* FUNCIONA APENAS COM PPM ASCII GERADO SEM COMENTARIOS, COMO NO CASO DO IMAGEMAGICK */

    GLuint texture;
    unsigned char * data;
    FILE * file;
    char linha2[255];
    int r,g,b;

    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( sizeof(char)*width * height * 3 );

    fgets(linha2,sizeof linha2, file);  // ignora P3
    fgets(linha2,sizeof linha2, file);  // ignora dimensoes
    fgets(linha2,sizeof linha2, file);  // ignora colordepth


    for (i=0; i<(width*height*3); i+=3)
    {
        fscanf(file,"%i %i %i",&r,&g,&b);
        data[i]=(unsigned char)r;
        data[i+1]=(unsigned char)g;
        data[i+2]=(unsigned char)b;
    }

    fclose( file );

    glGenTextures( 1, &texture ); //gera a textura
    glBindTexture( GL_TEXTURE_2D, texture ); // faz o binding da texture com o array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data );
    return texture;
}


