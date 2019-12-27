@insertpiece( SetCrossPlatformSettings )
@insertpiece( DeclUavCrossPlatform )

#if HW_PERFORMANCE == 0
#	define AA 1
#else
#	define AA 2  // make this 2 or 3 for antialiasing
#endif

uniform float2 mouse;
uniform float time;
uniform float frame;
uniform float2 resolution;

uniform float3 cameraPos;
uniform float3x3 cameraRot;

#define p_resolution resolution

#define p_mouse mouse
#define p_time time
#define p_frame frame
#define p_cameraPos cameraPos
#define p_cameraRot cameraRot

layout (@insertpiece(uav0_pf_type)) uniform restrict writeonly image2D renderTarget;

layout( local_size_x = @value( threads_per_group_x ),
		local_size_y = @value( threads_per_group_y ),
		local_size_z = @value( threads_per_group_z ) ) in;

@insertpiece( HeaderCS )

//in uvec3 gl_NumWorkGroups;
//in uvec3 gl_WorkGroupID;
//in uvec3 gl_LocalInvocationID;
//in uvec3 gl_GlobalInvocationID;
//in uint  gl_LocalInvocationIndex;

void main()
{
	@insertpiece( BodyCS )
}
