#version 330 core

out vec4 color;

float mapSphere (
	in vec3 p, 	// 3D point
	float r		// radius
) {
    return length(p) - r;
}

float mapWorld (
	in vec3 p
) {
	return length(p);
}

vec3 calculateNormal (
	in vec3 p
) {
    const vec3 small_step = vec3(0.001, 0.0, 0.0);

    float gradient_x = mapWorld(p + small_step.xyy) - mapWorld(p - small_step.xyy);
    float gradient_y = mapWorld(p + small_step.yxy) - mapWorld(p - small_step.yxy);
    float gradient_z = mapWorld(p + small_step.yyx) - mapWorld(p - small_step.yyx);

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}

vec3 rayMarch (
	in vec3 ro, // ray origin
	in vec3 rd 	// ray direction
) {
	float total_distance_traveled = 0.0;
    
	const int NUMBER_OF_STEPS = 32;
	const float MINIMUM_HIT_DISTANCE = 0.001;
	const float MAXIMUM_TRACE_DISTANCE = 1000.0;

    for (int i = 0; i < NUMBER_OF_STEPS; ++i) {
        vec3 current_position = ro + total_distance_traveled * rd;
        float distance_to_closest = mapSphere(current_position, 1.0);

        if (distance_to_closest < MINIMUM_HIT_DISTANCE) {
            vec3 surfaceNormal = calculateNormal(current_position);
            return surfaceNormal;
        }

        total_distance_traveled += distance_to_closest;
    }
    
	return vec3(0, 0, 0);
}

vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

void main() {
	vec2 uv = 2.0 * normalize(gl_FragCoord).xy - 1.0;

    vec3 camera_position = vec3(0.0, 0.0, 10.0);
    vec3 ro = camera_position;
    vec3 rd = rayDirection(45.0, vec2(480, 480), gl_FragCoord.xy);

	vec3 shadedColor = rayMarch(ro, rd);
	color = vec4(shadedColor, 1.0);
}
