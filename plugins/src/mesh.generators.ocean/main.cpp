#include "_configuration.h"
#include "vsx_param.h"
#include "vsx_module.h"
#include "main.h"
#include "vsx_math_3d.h"
//#include "vsx_string_lib.h"
#include "fftrefraction.h"


// TODO: map it on a tunnel!


class vsx_module_mesh_ocean : public vsx_module {
  // in
	// out
	vsx_module_param_mesh* result;
	// internal
	vsx_mesh mesh;
	//bool first_run;
	Alaska ocean;
public:
  void module_info(vsx_module_info* info)
  {
    info->identifier = "mesh;generators;ocean";
    info->description = "";
    info->in_param_spec = "";
    info->out_param_spec = "mesh:mesh";
    info->component_class = "mesh";
  }
  void declare_params(vsx_module_param_list& in_parameters, vsx_module_param_list& out_parameters)
  {
    loading_done = false;
  	result = (vsx_module_param_mesh*)out_parameters.create(VSX_MODULE_PARAM_ID_MESH,"mesh");
    result->set_p(mesh);
    //first_run = true;
    ocean.calculate_ho();
  }
  void run() {
    ocean.dtime = engine->real_vtime*0.1f;
    ocean.display();
    mesh.data->vertices.reset_used(0);
    mesh.data->vertex_normals.reset_used(0);
    mesh.data->vertex_tex_coords.reset_used(0);
    mesh.data->faces.reset_used(0);
    vsx_face face;
  	/*for (int L=0;L<2;L++)
  	{
  		for (int i=0;i<(BIG_NX-1);i++)
  		{
        unsigned long a = 0;
        unsigned long b = 0;
  			for (int k=0;k<2;k++)
  			{
          unsigned long a = 0;
  				for (int j=0;j<(BIG_NY);j++)
  				{
            mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i))/(float)NX*4.0f,(float)j/(float)NY*4.0f,0.0f));
  					//glTexCoord2f(((float)(i))/(float)NX*4,(float)j/(float)NY*4);
  					//glNormal3d(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]);
  					mesh.data->vertex_normals.push_back(vsx_vector__(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]));
  
  					//glVertex3f(
              //ocean.sea[i][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i][j][2]*ocean.scale_height);
  					b = mesh.data->vertices.push_back(vsx_vector__(ocean.sea[i][j][0]+L*MAX_WORLD_X,ocean.sea[i][j][1]+k*MAX_WORLD_Y,ocean.sea[i][j][2]*ocean.scale_height));
  					++a;
  					if (a >= 3) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
              //mesh.data->faces[f_count].a = a-3;
              //mesh.data->faces[f_count].b = a-2;
              //mesh.data->faces[f_count].c = a-1;
              //++f_count;
            }
            //printf("%d %d\n",i,j);
            mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4,0.0f));
  
  					//glTexCoord2f(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4);
  					mesh.data->vertex_normals.push_back(vsx_vector__(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]));
  					//glNormal3d(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]);
  
  					//glVertex3f(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i+1][j][2]*ocean.scale_height);


            b = mesh.data->vertices.push_back(vsx_vector__(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,ocean.sea[i+1][j][2]*ocean.scale_height));
            ++a;
  					if (a >= 4) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
            }
  				}
  			}
  		}
    }*/
for (int L=-1;L<2;L++)
  	{
  		for (int i=0;i<(BIG_NX-1);i++)
  		{
        unsigned long b = 0;
  			for (int k=-1;k<2;k++)
  			{
          unsigned long a = 0;
  				for (int j=0;j<(BIG_NY);j++)
  				{
            //mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i))/(float)NX*4.0f,(float)j/(float)NY*4.0f,0.0f));
  					//glTexCoord2f(((float)(i))/(float)NX*4,(float)j/(float)NY*4);
  					//glNormal3d(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]);
  					mesh.data->vertex_normals.push_back(vsx_vector(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]));
  
  					//glVertex3f(
              //ocean.sea[i][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i][j][2]*ocean.scale_height);
  					b = mesh.data->vertices.push_back(vsx_vector(ocean.sea[i][j][0]+L*MAX_WORLD_X,ocean.sea[i][j][1]+k*MAX_WORLD_Y,ocean.sea[i][j][2]*ocean.scale_height));
  					++a;
  					if (a >= 3) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
              //mesh.data->faces[f_count].a = a-3;
              //mesh.data->faces[f_count].b = a-2;
              //mesh.data->faces[f_count].c = a-1;
              //++f_count;
            }
            //printf("%d %d\n",i,j);
            //mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4,0.0f));
  
  					//glTexCoord2f(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4);
  					mesh.data->vertex_normals.push_back(vsx_vector(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]));
  					//glNormal3d(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]);
  
  					//glVertex3f(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i+1][j][2]*ocean.scale_height);


            b = mesh.data->vertices.push_back(vsx_vector(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,ocean.sea[i+1][j][2]*ocean.scale_height));
            ++a;
  					if (a >= 4) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
            }
  				}
  			}
  		}
  	}
    mesh.timestamp++;
    
    /*if (filename->get() != current_filename) {
      current_filename = filename->get();
      FILE *fp;
      if ((fp = fopen(current_filename.c_str(), "r")) == NULL)
        return;
      char buf[65535];
      vsx_string line;
      vsx_avector<vsx_vector> normals;
      vsx_avector<vsx_vector> texcoords;
      while (fgets(buf,65535,fp)) {
        line = buf;
        if (line[line.size()-1] == 0x0A) line.pop_back();
        if (line[line.size()-1] == 0x0D) line.pop_back();
        //printf("reading line: %s\n",line.c_str());
        if (line.size()) {
          vsx_avector<vsx_string> parts;
          vsx_string deli = " ";
          explode(line, deli, parts);
          if (parts[0] == "v") {
            mesh.data->vertices.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else 
          if (parts[0] == "vt") {
            texcoords.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else
          if (parts[0] == "vn") {
            normals.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
            //mesh.data->vertex_normals.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else
          if (parts[0] == "f") {
            if (parts.size() == 4) {
              vsx_face ff;
              vsx_avector<vsx_string> parts2;
              vsx_string deli2 = "/";
  
              explode(parts[1], deli2, parts2);
              ff.a = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.a] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.a] = texcoords[s2i(parts2[1])-1];
    
              explode(parts[2], deli2, parts2);
              ff.b = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.b] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.b] = texcoords[s2i(parts2[1])-1];
    
              explode(parts[3], deli2, parts2);
              ff.c = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.c] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.c] = texcoords[s2i(parts2[1])-1];
    
              mesh.data->faces.push_back(ff);
            }
          }
        }  
      }
      fclose(fp);
      loading_done = true;
    }*/
    loading_done = true;
    result->set_p(mesh);
  }
  
  void on_delete() {
    mesh.clear();
  }
};



class vsx_module_mesh_ocean_tunnel : public vsx_module {
  // in
  vsx_module_param_float* time_speed;
	// out
	vsx_module_param_mesh* result;
	// internal
	vsx_mesh mesh;
	//bool first_run;
	Alaska ocean;
	float t;
public:
  void module_info(vsx_module_info* info)
  {
    info->identifier = "mesh;generators;ocean_tunnel";
    info->description = "";
    info->in_param_spec = "time_speed:float";
    info->out_param_spec = "mesh:mesh";
    info->component_class = "mesh";
  }
  void declare_params(vsx_module_param_list& in_parameters, vsx_module_param_list& out_parameters)
  {
    loading_done = false;
    time_speed = (vsx_module_param_float*)in_parameters.create(VSX_MODULE_PARAM_ID_FLOAT,"time_speed");
    time_speed->set(0.2f);
  	result = (vsx_module_param_mesh*)out_parameters.create(VSX_MODULE_PARAM_ID_MESH,"mesh");
    result->set_p(mesh);
    //first_run = true;
    ocean.calculate_ho();
    t = 0;
  }
  void run() {
  	t += time_speed->get()*engine->real_dtime;
    ocean.dtime = t;
    ocean.display();
    mesh.data->vertices.reset_used(0);
    mesh.data->vertex_normals.reset_used(0);
    mesh.data->vertex_tex_coords.reset_used(0);
    mesh.data->faces.reset_used(0);
    vsx_face face;
  	/*for (int L=0;L<2;L++)
  	{
  		for (int i=0;i<(BIG_NX-1);i++)
  		{
        unsigned long a = 0;
        unsigned long b = 0;
  			for (int k=0;k<2;k++)
  			{
          unsigned long a = 0;
  				for (int j=0;j<(BIG_NY);j++)
  				{
            mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i))/(float)NX*4.0f,(float)j/(float)NY*4.0f,0.0f));
  					//glTexCoord2f(((float)(i))/(float)NX*4,(float)j/(float)NY*4);
  					//glNormal3d(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]);
  					mesh.data->vertex_normals.push_back(vsx_vector__(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]));
  
  					//glVertex3f(
              //ocean.sea[i][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i][j][2]*ocean.scale_height);
  					b = mesh.data->vertices.push_back(vsx_vector__(ocean.sea[i][j][0]+L*MAX_WORLD_X,ocean.sea[i][j][1]+k*MAX_WORLD_Y,ocean.sea[i][j][2]*ocean.scale_height));
  					++a;
  					if (a >= 3) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
              //mesh.data->faces[f_count].a = a-3;
              //mesh.data->faces[f_count].b = a-2;
              //mesh.data->faces[f_count].c = a-1;
              //++f_count;
            }
            //printf("%d %d\n",i,j);
            mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4,0.0f));
  
  					//glTexCoord2f(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4);
  					mesh.data->vertex_normals.push_back(vsx_vector__(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]));
  					//glNormal3d(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]);
  
  					//glVertex3f(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i+1][j][2]*ocean.scale_height);


            b = mesh.data->vertices.push_back(vsx_vector__(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,ocean.sea[i+1][j][2]*ocean.scale_height));
            ++a;
  					if (a >= 4) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
            }
  				}
  			}
  		}
    }*/
    vsx_vector g;
    vsx_vector c;
    //float xmax = 0;
    //float xmin = 0;
  	for (int L=-1;L<2;L++)
  	{
  		for (int i=0;i<(BIG_NX-1);i++)
  		{
        unsigned long b = 0;
  			for (int k=-1;k<2;k++)
  			{
          unsigned long a = 0;
  				for (int j=0;j<(BIG_NY);j++)
  				{
  					if (j%2 == 1) continue;
            //mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i))/(float)NX*4.0f,(float)j/(float)NY*4.0f,0.0f));
  					//glTexCoord2f(((float)(i))/(float)NX*4,(float)j/(float)NY*4);
  					//glNormal3d(ocean.big_normals[i][j][0],ocean.big_normals[i][j][1],ocean.big_normals[i][j][2]);
  
  					//glVertex3f(
              //ocean.sea[i][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i][j][2]*ocean.scale_height);
#define TDIV (float)MAX_WORLD_X
#define TD2  (float)MAX_WORLD_X*0.5f
///  					b = mesh.data->vertices.push_back(vsx_vector(ocean.sea[i][j][0]+L*MAX_WORLD_X,ocean.sea[i][j][1]+k*MAX_WORLD_Y,ocean.sea[i][j][2]*ocean.scale_height));
						//if (ocean.sea[i][j][1] < xmin) xmin = ocean.sea[i][j][1];
						//if (ocean.sea[i][j][1] > xmax) xmax = ocean.sea[i][j][1];
						g.x = ocean.sea[i][j][0];//+L*MAX_WORLD_X;
						g.y = ocean.sea[i][j][1];//+k*MAX_WORLD_Y;
						g.z = ocean.sea[i][j][2];//*ocean.scale_height;

					//printf("%f\n",g.x/(float)TDIV);
						float gr = \
						PI*2.0f * g.x/(TDIV);
  					float nra = gr + 90.0f / 360.0f * 2*PI; 


						vsx_vector nn;
						nn.x = ocean.big_normals[i][j][0];
						nn.y = ocean.big_normals[i][j][1];
						nn.normalize();
  					mesh.data->vertex_normals.push_back(vsx_vector(\
  						nn.x* cos(nra) + nn.y * -sin(nra),\
  						nn.x* sin(nra) + nn.y * cos(nra),\
  						ocean.big_normals[i][j][2]));
  					mesh.data->vertex_normals[mesh.data->vertex_normals.size()-1].normalize();

						
						float gz = 2.0f+fabs(g.z)*1.5f;
						c.x = cos(gr)*gz;
						c.y = sin(gr)*gz;
						c.z = g.y*2.0f;
  					b = mesh.data->vertices.push_back(c);
						mesh.data->vertex_tex_coords.push_back(vsx_tex_coord__(fabs(g.x-TD2)*2.0f , fabs(g.y-TD2)*2.0f));
  					++a;
  					if (a >= 3) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
              //mesh.data->faces[f_count].a = a-3;
              //mesh.data->faces[f_count].b = a-2;
              //mesh.data->faces[f_count].c = a-1;
              //++f_count;
            }
            //printf("%d %d\n",i,j);
            //mesh.data->vertex_tex_coords.push_back(vsx_vector__(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4,0.0f));
  
  					//glTexCoord2f(((float)(i)+1)/(float)NX*4,(float)j/(float)NY*4);
  					//mesh.data->vertex_normals.push_back(vsx_vector(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]));
  					//glNormal3d(ocean.big_normals[i+1][j][0],ocean.big_normals[i+1][j][1],ocean.big_normals[i+1][j][2]);
  
  					//glVertex3f(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,
  						//ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,
  						//ocean.sea[i+1][j][2]*ocean.scale_height);


            //b = mesh.data->vertices.push_back(vsx_vector(ocean.sea[i+1][j][0]+L*MAX_WORLD_X,ocean.sea[i+1][j][1]+k*MAX_WORLD_Y,ocean.sea[i+1][j][2]*ocean.scale_height));
						//++a;
						g.x = ocean.sea[i+1][j][0];//+L*MAX_WORLD_X;
						g.y = ocean.sea[i+1][j][1];//+k*MAX_WORLD_Y;
						g.z = ocean.sea[i+1][j][2];//*ocean.scale_height;

						gr = \
						PI*2.0f* g.x/(TDIV);
						nra = gr + 90.0f / 360.0f * 2*PI;
						
						
						nn.x = ocean.big_normals[i+1][j][0];
						nn.y = ocean.big_normals[i+1][j][1];
						nn.normalize();
  					mesh.data->vertex_normals.push_back(vsx_vector(\
  						nn.x* cos(nra) + nn.y * -sin(nra),\
  						nn.x* sin(nra) + nn.y * cos(nra),\
  						ocean.big_normals[i+1][j][2]));
//  						ocean.big_normals[i+1][j][0]* cos(nra) + ocean.big_normals[i+1][j][1] * -sin(nra),
//  						ocean.big_normals[i+1][j][0]* sin(nra) + ocean.big_normals[i+1][j][1] * cos(nra),

  					mesh.data->vertex_normals[mesh.data->vertex_normals.size()-1].normalize();
						
						gz = 2.0f+fabs(g.z)*1.5f;
						c.x = cos(gr)*gz;
						c.y = sin(gr)*gz;
						c.z = g.y*2.0f;
  					b = mesh.data->vertices.push_back(c);
  					
						mesh.data->vertex_tex_coords.push_back(vsx_tex_coord__(fabs(g.x-TD2)*2.0f , fabs(g.y-TD2)*2.0f));
            
            ++a;

  					if (a >= 4) {
              face.a = b-3;
              face.b = b-2;
              face.c = b-1;
              mesh.data->faces.push_back(face);
            }
  				}
  			}
  		}
  	}
    //printf("xmax: %f\nxmin: %f\n",xmax,xmin);
    
    
    /*if (filename->get() != current_filename) {
      current_filename = filename->get();
      FILE *fp;
      if ((fp = fopen(current_filename.c_str(), "r")) == NULL)
        return;
      char buf[65535];
      vsx_string line;
      vsx_avector<vsx_vector> normals;
      vsx_avector<vsx_vector> texcoords;
      while (fgets(buf,65535,fp)) {
        line = buf;
        if (line[line.size()-1] == 0x0A) line.pop_back();
        if (line[line.size()-1] == 0x0D) line.pop_back();
        //printf("reading line: %s\n",line.c_str());
        if (line.size()) {
          vsx_avector<vsx_string> parts;
          vsx_string deli = " ";
          explode(line, deli, parts);
          if (parts[0] == "v") {
            mesh.data->vertices.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else 
          if (parts[0] == "vt") {
            texcoords.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else
          if (parts[0] == "vn") {
            normals.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
            //mesh.data->vertex_normals.push_back(vsx_vector__(s2f(parts[1]),s2f(parts[2]),s2f(parts[3])));
          } else
          if (parts[0] == "f") {
            if (parts.size() == 4) {
              vsx_face ff;
              vsx_avector<vsx_string> parts2;
              vsx_string deli2 = "/";
  
              explode(parts[1], deli2, parts2);
              ff.a = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.a] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.a] = texcoords[s2i(parts2[1])-1];
    
              explode(parts[2], deli2, parts2);
              ff.b = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.b] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.b] = texcoords[s2i(parts2[1])-1];
    
              explode(parts[3], deli2, parts2);
              ff.c = s2i(parts2[0])-1;
              mesh.data->vertex_normals[ff.c] = normals[s2i(parts2[1])-1];
              mesh.data->vertex_tex_coords[ff.c] = texcoords[s2i(parts2[1])-1];
    
              mesh.data->faces.push_back(ff);
            }
          }
        }  
      }
      fclose(fp);
      loading_done = true;
    }*/
    loading_done = true;
    result->set_p(mesh);
  }
  
  void on_delete() {
    mesh.clear();
  }
};


//******************************************************************************************
//******************************************************************************************
//******************************************************************************************

vsx_module* create_new_module(unsigned long module) {
  switch(module) {
    case 0: return (vsx_module*)(new vsx_module_mesh_ocean);
    case 1: return (vsx_module*)(new vsx_module_mesh_ocean_tunnel);
  }
  return 0;
}

void destroy_module(vsx_module* m,unsigned long module) {
  switch(module) {
    case 0: delete (vsx_module_mesh_ocean*)m; break;
    case 1: delete (vsx_module_mesh_ocean_tunnel*)m; break;
  }
}

unsigned long get_num_modules() {
  // we have only one module. it's id is 0
  return 2;
}


