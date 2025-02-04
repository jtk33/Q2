#include "g_local.h"
void ApplyThrust(edict_t *ent)
{

	vec3_t forward, right;
	vec3_t pack_pos, jet_vector;


	if (ent->velocity[2] < -250)
		ent->velocity[2] += ((ent->velocity[2]) / (-5));
	else if (ent->velocity[2] < 0)
		ent->velocity[2] += 100;
	else
		ent->velocity[2] += ((250 - ent->velocity[2]) / 8);


	AngleVectors(ent->client->v_angle, forward, right, NULL);
	VectorScale(forward, -7, pack_pos);
	VectorAdd(pack_pos, ent->s.origin, pack_pos);
	pack_pos[2] += (ent->viewheight);

	VectorScale(forward, -50, jet_vector);

	gi.WriteByte(svc_temp_entity);
	gi.WriteByte(TE_SPARKS);
	gi.WritePosition(pack_pos);
	gi.WriteDir(jet_vector);
	gi.multicast(pack_pos, MULTICAST_PVS);


	if (ent->client->next_thrust_sound < level.time)
	{
		gi.sound(ent, CHAN_BODY, gi.soundindex("weapons/rockfly.wav"), 1, ATTN_NORM, 0);
		ent->client->next_thrust_sound = level.time + 1.0;
	}
}