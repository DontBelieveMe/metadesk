// generated by W:/metadesk/examples/type_metadata/type_metadata.c:914
TypeInfoMember Circle_members[2] = {
{"r", 1, -1, &F32_type_info},
{"pos", 3, -1, &V2F32_type_info},
};
TypeInfoMember RoundedSegment_members[3] = {
{"r", 1, -1, &F32_type_info},
{"p1", 2, -1, &V2F32_type_info},
{"p2", 2, -1, &V2F32_type_info},
};
TypeInfoMember RoundedPolygon_members[3] = {
{"r", 1, -1, &F32_type_info},
{"count", 5, -1, &U32_type_info},
{"p", 1, 1, &V2F32_type_info},
};

// generated by W:/metadesk/examples/type_metadata/type_metadata.c:953
TypeInfoEnumerant Shape_members[3] = {
{"Circle", 6, 1},
{"Segment", 7, 2},
{"Polygon", 7, 3},
};

// generated by W:/metadesk/examples/type_metadata/type_metadata.c:989
TypeInfo U32_type_info = {TypeKind_Basic, "U32", 3, 4, 0, 0};
TypeInfo F32_type_info = {TypeKind_Basic, "F32", 3, 4, 0, 0};
TypeInfo V2F32_type_info = {TypeKind_Basic, "V2F32", 5, 8, 0, 0};
TypeInfo Circle_type_info = {TypeKind_Struct, "Circle", 6, 2, Circle_members, 0};
TypeInfo RoundedSegment_type_info = {TypeKind_Struct, "RoundedSegment", 14, 3, RoundedSegment_members, 0};
TypeInfo RoundedPolygon_type_info = {TypeKind_Struct, "RoundedPolygon", 14, 3, RoundedPolygon_members, 0};
TypeInfo Shape_type_info = {TypeKind_Enum, "Shape", 5, 3, Shape_members, &U32_type_info};

// generated by W:/metadesk/examples/type_metadata/type_metadata.c:1049
TypeInfo*
type_info_from_shape(Shape v)
{
TypeInfo* result;
switch (v)
{
default:
{
result = 0;
}break;
case Shape_Circle:
{
result = &Circle_type_info;
}break;
case Shape_Segment:
{
result = &RoundedSegment_type_info;
}break;
case Shape_Polygon:
{
result = &RoundedPolygon_type_info;
}break;
}
return(result);
}
U32
max_slot_from_shape(Shape v)
{
U32 result;
switch (v)
{
default:
{
result = 0;
}break;
case Shape_Circle:
case Shape_Segment:
{
result = 64;
}break;
case Shape_Polygon:
{
result = 12;
}break;
}
return(result);
}

