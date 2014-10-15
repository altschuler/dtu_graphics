// 02561-01-07

#include "Angel.h"
#include <vector>

using namespace std;

const int NumTimesToSubdivide = 5;

vector<vec2> points;
int Index = 0;

//----------------------------------------------------------------------------

void square(const vec2& a, const vec2& b, const vec2& c, const vec2& d) {
	// draw the square as two triangles across the diagonal
    points.push_back(a);
	points.push_back(b);
	points.push_back(c);

	points.push_back(a);
	points.push_back(c);
	points.push_back(d);
}

//----------------------------------------------------------------------------

void divide_square(const vec2& a, const vec2& b, const vec2& c, const vec2& d, int count) {
    if (count > 0) {
		// side length of the *sub-square* of the current square
		const float d = length((b - a) / 3.0f);

		// utility vectors in the x and y directions used to computed
		// sub-squares easily
		const vec2 dx(d, 0.0f);
		const vec2 dy(0.0f, d);

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				// leave the center square white
				if (x == 1 && y == 1) continue;

				// compute the sub-square coordinates using the (x,y)
				// pair and the side lengths defined earlier
				divide_square(a + x*dx     + y*dy,
							  a + (x+1)*dx + y*dy,
							  a + (x+1)*dx + (y+1)*dy,
							  a + x*dx     + (y+1)*dy,
							  count - 1);
			}
		}
    } else {
		// leaf, draw a black square
        square( a, b, c, d );
    }
}

//----------------------------------------------------------------------------

void init( void ) {
    vec2 vertices[4] = {
        vec2( -1.0, -1.0 ),
		vec2(  1.0, -1.0 ),
		vec2(  1.0,  1.0 ),
        vec2( -1.0,  1.0 )
    };

    // Subdivide the original square
    divide_square( vertices[0], vertices[1], vertices[2], vertices[3],
				   NumTimesToSubdivide );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec2)*points.size(), &points[0], GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "const-shader.vert", "const-shader.frag", "fragColor" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "position" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void display( void ) {
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_TRIANGLES, 0, points.size() );
    glFlush();
	Angel::CheckError();
}

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

int main( int argc, char **argv ) {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA|GLUT_3_2_CORE_PROFILE );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "02561-01-07" );

	Angel::InitOpenGL();

    init();

    glutDisplayFunc( display );

	Angel::CheckError();

    glutMainLoop();
    return 0;
}
