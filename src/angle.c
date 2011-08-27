/*!
 * \brief renvoie la rotation en degrée la plus courte pour passer d'un angle à un autre
 */
double angle_shortener_rotation (double angle1, double angle2)
{
	if (angle2 > angle1 + 180.0)
	{
		angle2 = angle2 - 360;
	}
	
	angle1 = angle1 - angle2;
	return -angle1;
}