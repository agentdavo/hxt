// Gmsh - Copyright (C) 1997-2017 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@onelab.info>.

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <string>
#include "ColorTable.h"

#define GMSH_SET         (1<<0)
#define GMSH_GET         (1<<1)
#define GMSH_GUI         (1<<2)
#define GMSH_SET_DEFAULT (1<<3)
#define GMSH_GET_DEFAULT (1<<4)

#define GMSH_SESSIONRC (1<<0)
#define GMSH_OPTIONSRC (1<<1)
#define GMSH_FULLRC    (1<<2)

// action is a combination of GMSH_SET, GMSH_GET, GMSH_GUI

#define OPT_ARGS_STR   int num, int action, std::string val
#define OPT_ARGS_NUM   int num, int action, double val
#define OPT_ARGS_COL   int num, int action, unsigned int val

// STRINGS

std::string opt_general_axes_label0(OPT_ARGS_STR);
std::string opt_general_axes_label1(OPT_ARGS_STR);
std::string opt_general_axes_label2(OPT_ARGS_STR);
std::string opt_general_axes_format0(OPT_ARGS_STR);
std::string opt_general_axes_format1(OPT_ARGS_STR);
std::string opt_general_axes_format2(OPT_ARGS_STR);
std::string opt_general_background_image_filename(OPT_ARGS_STR);
std::string opt_general_display(OPT_ARGS_STR);
std::string opt_general_version(OPT_ARGS_STR);
std::string opt_general_build_options(OPT_ARGS_STR);
std::string opt_general_filename(OPT_ARGS_STR);
std::string opt_general_executable_filename(OPT_ARGS_STR);
std::string opt_general_default_filename(OPT_ARGS_STR);
std::string opt_general_tmp_filename(OPT_ARGS_STR);
std::string opt_general_error_filename(OPT_ARGS_STR);
std::string opt_general_session_filename(OPT_ARGS_STR);
std::string opt_general_options_filename(OPT_ARGS_STR);
std::string opt_general_recent_file0(OPT_ARGS_STR);
std::string opt_general_recent_file1(OPT_ARGS_STR);
std::string opt_general_recent_file2(OPT_ARGS_STR);
std::string opt_general_recent_file3(OPT_ARGS_STR);
std::string opt_general_recent_file4(OPT_ARGS_STR);
std::string opt_general_recent_file5(OPT_ARGS_STR);
std::string opt_general_recent_file6(OPT_ARGS_STR);
std::string opt_general_recent_file7(OPT_ARGS_STR);
std::string opt_general_recent_file8(OPT_ARGS_STR);
std::string opt_general_recent_file9(OPT_ARGS_STR);
std::string opt_general_editor(OPT_ARGS_STR);
std::string opt_general_watch_file_pattern(OPT_ARGS_STR);
std::string opt_general_gui_theme(OPT_ARGS_STR);
std::string opt_general_graphics_font(OPT_ARGS_STR);
std::string opt_general_graphics_font_title(OPT_ARGS_STR);
std::string opt_general_graphics_font_engine(OPT_ARGS_STR);
std::string opt_geometry_double_clicked_point_command(OPT_ARGS_STR);
std::string opt_geometry_double_clicked_line_command(OPT_ARGS_STR);
std::string opt_geometry_double_clicked_surface_command(OPT_ARGS_STR);
std::string opt_geometry_double_clicked_volume_command(OPT_ARGS_STR);
std::string opt_geometry_occ_target_unit(OPT_ARGS_STR);
std::string opt_solver_socket_name(OPT_ARGS_STR);
std::string opt_solver_name(OPT_ARGS_STR);
std::string opt_solver_name0(OPT_ARGS_STR);
std::string opt_solver_name1(OPT_ARGS_STR);
std::string opt_solver_name2(OPT_ARGS_STR);
std::string opt_solver_name3(OPT_ARGS_STR);
std::string opt_solver_name4(OPT_ARGS_STR);
std::string opt_solver_name5(OPT_ARGS_STR);
std::string opt_solver_name6(OPT_ARGS_STR);
std::string opt_solver_name7(OPT_ARGS_STR);
std::string opt_solver_name8(OPT_ARGS_STR);
std::string opt_solver_name9(OPT_ARGS_STR);
std::string opt_solver_extension(OPT_ARGS_STR);
std::string opt_solver_extension0(OPT_ARGS_STR);
std::string opt_solver_extension1(OPT_ARGS_STR);
std::string opt_solver_extension2(OPT_ARGS_STR);
std::string opt_solver_extension3(OPT_ARGS_STR);
std::string opt_solver_extension4(OPT_ARGS_STR);
std::string opt_solver_extension5(OPT_ARGS_STR);
std::string opt_solver_extension6(OPT_ARGS_STR);
std::string opt_solver_extension7(OPT_ARGS_STR);
std::string opt_solver_extension8(OPT_ARGS_STR);
std::string opt_solver_extension9(OPT_ARGS_STR);
std::string opt_solver_executable(OPT_ARGS_STR);
std::string opt_solver_executable0(OPT_ARGS_STR);
std::string opt_solver_executable1(OPT_ARGS_STR);
std::string opt_solver_executable2(OPT_ARGS_STR);
std::string opt_solver_executable3(OPT_ARGS_STR);
std::string opt_solver_executable4(OPT_ARGS_STR);
std::string opt_solver_executable5(OPT_ARGS_STR);
std::string opt_solver_executable6(OPT_ARGS_STR);
std::string opt_solver_executable7(OPT_ARGS_STR);
std::string opt_solver_executable8(OPT_ARGS_STR);
std::string opt_solver_executable9(OPT_ARGS_STR);
std::string opt_solver_remote_login(OPT_ARGS_STR);
std::string opt_solver_remote_login0(OPT_ARGS_STR);
std::string opt_solver_remote_login1(OPT_ARGS_STR);
std::string opt_solver_remote_login2(OPT_ARGS_STR);
std::string opt_solver_remote_login3(OPT_ARGS_STR);
std::string opt_solver_remote_login4(OPT_ARGS_STR);
std::string opt_solver_remote_login5(OPT_ARGS_STR);
std::string opt_solver_remote_login6(OPT_ARGS_STR);
std::string opt_solver_remote_login7(OPT_ARGS_STR);
std::string opt_solver_remote_login8(OPT_ARGS_STR);
std::string opt_solver_remote_login9(OPT_ARGS_STR);
std::string opt_solver_octave_interpreter(OPT_ARGS_STR);
std::string opt_solver_python_interpreter(OPT_ARGS_STR);
std::string opt_post_double_clicked_graph_point_command(OPT_ARGS_STR);
std::string opt_view_name(OPT_ARGS_STR);
std::string opt_view_format(OPT_ARGS_STR);
std::string opt_view_filename(OPT_ARGS_STR);
std::string opt_view_double_clicked_command(OPT_ARGS_STR);
std::string opt_view_group(OPT_ARGS_STR);
std::string opt_view_axes_label0(OPT_ARGS_STR);
std::string opt_view_axes_label1(OPT_ARGS_STR);
std::string opt_view_axes_label2(OPT_ARGS_STR);
std::string opt_view_axes_format0(OPT_ARGS_STR);
std::string opt_view_axes_format1(OPT_ARGS_STR);
std::string opt_view_axes_format2(OPT_ARGS_STR);
std::string opt_view_gen_raise0(OPT_ARGS_STR);
std::string opt_view_gen_raise1(OPT_ARGS_STR);
std::string opt_view_gen_raise2(OPT_ARGS_STR);
std::string opt_view_stipple0(OPT_ARGS_STR);
std::string opt_view_stipple1(OPT_ARGS_STR);
std::string opt_view_stipple2(OPT_ARGS_STR);
std::string opt_view_stipple3(OPT_ARGS_STR);
std::string opt_view_stipple4(OPT_ARGS_STR);
std::string opt_view_stipple5(OPT_ARGS_STR);
std::string opt_view_stipple6(OPT_ARGS_STR);
std::string opt_view_stipple7(OPT_ARGS_STR);
std::string opt_view_stipple8(OPT_ARGS_STR);
std::string opt_view_stipple9(OPT_ARGS_STR);
std::string opt_view_attributes(OPT_ARGS_STR);
std::string opt_print_parameter_command(OPT_ARGS_STR);

// NUMBERS

double opt_general_initial_context(OPT_ARGS_NUM);
double opt_general_show_options_on_startup(OPT_ARGS_NUM);
double opt_general_show_messages_on_startup(OPT_ARGS_NUM);
double opt_general_fontsize(OPT_ARGS_NUM);
double opt_general_gui_color_scheme(OPT_ARGS_NUM);
double opt_general_graphics_fontsize(OPT_ARGS_NUM);
double opt_general_graphics_fontsize_title(OPT_ARGS_NUM);
double opt_general_graphics_position0(OPT_ARGS_NUM);
double opt_general_graphics_position1(OPT_ARGS_NUM);
double opt_general_graphics_size0(OPT_ARGS_NUM);
double opt_general_graphics_size1(OPT_ARGS_NUM);
double opt_general_context_position0(OPT_ARGS_NUM);
double opt_general_context_position1(OPT_ARGS_NUM);
double opt_general_file_chooser_position0(OPT_ARGS_NUM);
double opt_general_file_chooser_position1(OPT_ARGS_NUM);
double opt_general_polygon_offset_always(OPT_ARGS_NUM);
double opt_general_polygon_offset_factor(OPT_ARGS_NUM);
double opt_general_polygon_offset_units(OPT_ARGS_NUM);
double opt_general_system_menu_bar(OPT_ARGS_NUM);
double opt_general_meshdiscrete(OPT_ARGS_NUM);
double opt_general_message_size(OPT_ARGS_NUM);
double opt_general_message_fontsize(OPT_ARGS_NUM);
double opt_general_detached_menu(OPT_ARGS_NUM);
double opt_general_menu_size0(OPT_ARGS_NUM);
double opt_general_menu_size1(OPT_ARGS_NUM);
double opt_general_menu_position0(OPT_ARGS_NUM);
double opt_general_menu_position1(OPT_ARGS_NUM);
double opt_general_option_position0(OPT_ARGS_NUM);
double opt_general_option_position1(OPT_ARGS_NUM);
double opt_general_plugin_position0(OPT_ARGS_NUM);
double opt_general_plugin_position1(OPT_ARGS_NUM);
double opt_general_plugin_size0(OPT_ARGS_NUM);
double opt_general_plugin_size1(OPT_ARGS_NUM);
double opt_general_field_position0(OPT_ARGS_NUM);
double opt_general_field_position1(OPT_ARGS_NUM);
double opt_general_field_size0(OPT_ARGS_NUM);
double opt_general_field_size1(OPT_ARGS_NUM);
double opt_general_extra_position0(OPT_ARGS_NUM);
double opt_general_extra_position1(OPT_ARGS_NUM);
double opt_general_extra_size0(OPT_ARGS_NUM);
double opt_general_extra_size1(OPT_ARGS_NUM);
double opt_general_statistics_position0(OPT_ARGS_NUM);
double opt_general_statistics_position1(OPT_ARGS_NUM);
double opt_general_visibility_position0(OPT_ARGS_NUM);
double opt_general_visibility_position1(OPT_ARGS_NUM);
double opt_general_clip_position0(OPT_ARGS_NUM);
double opt_general_clip_position1(OPT_ARGS_NUM);
double opt_general_manip_position0(OPT_ARGS_NUM);
double opt_general_manip_position1(OPT_ARGS_NUM);
double opt_general_hot_position0(OPT_ARGS_NUM);
double opt_general_hot_position1(OPT_ARGS_NUM);
double opt_general_high_resolution_graphics(OPT_ARGS_NUM);
double opt_general_high_resolution_point_size_factor(OPT_ARGS_NUM);
double opt_general_session_save(OPT_ARGS_NUM);
double opt_general_options_save(OPT_ARGS_NUM);
double opt_general_rotation0(OPT_ARGS_NUM);
double opt_general_rotation1(OPT_ARGS_NUM);
double opt_general_rotation2(OPT_ARGS_NUM);
double opt_general_rotation_center0(OPT_ARGS_NUM);
double opt_general_rotation_center1(OPT_ARGS_NUM);
double opt_general_rotation_center2(OPT_ARGS_NUM);
double opt_general_quaternion0(OPT_ARGS_NUM);
double opt_general_quaternion1(OPT_ARGS_NUM);
double opt_general_quaternion2(OPT_ARGS_NUM);
double opt_general_quaternion3(OPT_ARGS_NUM);
double opt_general_translation0(OPT_ARGS_NUM);
double opt_general_translation1(OPT_ARGS_NUM);
double opt_general_translation2(OPT_ARGS_NUM);
double opt_general_scale0(OPT_ARGS_NUM);
double opt_general_scale1(OPT_ARGS_NUM);
double opt_general_scale2(OPT_ARGS_NUM);
double opt_general_clip_factor(OPT_ARGS_NUM);
double opt_general_display_border_factor(OPT_ARGS_NUM);
double opt_general_point_size(OPT_ARGS_NUM);
double opt_general_line_width(OPT_ARGS_NUM);
double opt_general_shine(OPT_ARGS_NUM);
double opt_general_shine_exponent(OPT_ARGS_NUM);
double opt_general_color_scheme(OPT_ARGS_NUM);
double opt_general_background_gradient(OPT_ARGS_NUM);
double opt_general_background_image_position0(OPT_ARGS_NUM);
double opt_general_background_image_position1(OPT_ARGS_NUM);
double opt_general_background_image_size0(OPT_ARGS_NUM);
double opt_general_background_image_size1(OPT_ARGS_NUM);
double opt_general_background_image_3d(OPT_ARGS_NUM);
double opt_general_background_image_page(OPT_ARGS_NUM);
double opt_general_verbosity(OPT_ARGS_NUM);
double opt_general_progress_meter_step(OPT_ARGS_NUM);
double opt_general_nopopup(OPT_ARGS_NUM);
double opt_general_non_modal_windows(OPT_ARGS_NUM);
double opt_general_terminal(OPT_ARGS_NUM);
double opt_general_tooltips(OPT_ARGS_NUM);
double opt_general_confirm_overwrite(OPT_ARGS_NUM);
double opt_general_orthographic(OPT_ARGS_NUM);
double opt_general_mouse_selection(OPT_ARGS_NUM);
double opt_general_mouse_hover_meshes(OPT_ARGS_NUM);
double opt_general_draw_bounding_box(OPT_ARGS_NUM);
double opt_general_draw_oriented_bounding_box(OPT_ARGS_NUM);
double opt_general_fast_redraw(OPT_ARGS_NUM);
double opt_general_xmin(OPT_ARGS_NUM);
double opt_general_xmax(OPT_ARGS_NUM);
double opt_general_ymin(OPT_ARGS_NUM);
double opt_general_ymax(OPT_ARGS_NUM);
double opt_general_zmin(OPT_ARGS_NUM);
double opt_general_zmax(OPT_ARGS_NUM);
double opt_general_lc(OPT_ARGS_NUM);
double opt_general_axes(OPT_ARGS_NUM);
double opt_general_axes_mikado(OPT_ARGS_NUM);
double opt_general_axes_auto_position(OPT_ARGS_NUM);
double opt_general_axes_xmin(OPT_ARGS_NUM);
double opt_general_axes_xmax(OPT_ARGS_NUM);
double opt_general_axes_ymin(OPT_ARGS_NUM);
double opt_general_axes_ymax(OPT_ARGS_NUM);
double opt_general_axes_zmin(OPT_ARGS_NUM);
double opt_general_axes_zmax(OPT_ARGS_NUM);
double opt_general_axes_tics0(OPT_ARGS_NUM);
double opt_general_axes_tics1(OPT_ARGS_NUM);
double opt_general_axes_tics2(OPT_ARGS_NUM);
double opt_general_axes_force_value(OPT_ARGS_NUM);
double opt_general_axes_value_xmin(OPT_ARGS_NUM);
double opt_general_axes_value_xmax(OPT_ARGS_NUM);
double opt_general_axes_value_ymin(OPT_ARGS_NUM);
double opt_general_axes_value_ymax(OPT_ARGS_NUM);
double opt_general_axes_value_zmin(OPT_ARGS_NUM);
double opt_general_axes_value_zmax(OPT_ARGS_NUM);
double opt_general_small_axes(OPT_ARGS_NUM);
double opt_general_small_axes_position0(OPT_ARGS_NUM);
double opt_general_small_axes_position1(OPT_ARGS_NUM);
double opt_general_small_axes_size(OPT_ARGS_NUM);
double opt_general_quadric_subdivisions(OPT_ARGS_NUM);
double opt_general_double_buffer(OPT_ARGS_NUM);
double opt_general_antialiasing(OPT_ARGS_NUM);
double opt_general_alpha_blending(OPT_ARGS_NUM);
double opt_general_vector_type(OPT_ARGS_NUM);
double opt_general_arrow_head_radius(OPT_ARGS_NUM);
double opt_general_arrow_stem_length(OPT_ARGS_NUM);
double opt_general_arrow_stem_radius(OPT_ARGS_NUM);
double opt_general_trackball(OPT_ARGS_NUM);
double opt_general_trackball_hyperbolic_sheet(OPT_ARGS_NUM);
double opt_general_gamepad(OPT_ARGS_NUM);
double opt_general_rotation_center_cg(OPT_ARGS_NUM);
double opt_general_zoom_factor(OPT_ARGS_NUM);
double opt_general_expert_mode(OPT_ARGS_NUM);
double opt_general_stereo_mode(OPT_ARGS_NUM);
double opt_general_camera_mode(OPT_ARGS_NUM);
#if defined(HAVE_VISUDEV)
double opt_general_heavy_visualization(OPT_ARGS_NUM);
#endif
double opt_general_eye_sep_ratio(OPT_ARGS_NUM);
double opt_general_focallength_ratio(OPT_ARGS_NUM);
double opt_general_camera_aperture(OPT_ARGS_NUM);
double opt_general_clip0a(OPT_ARGS_NUM);
double opt_general_clip0b(OPT_ARGS_NUM);
double opt_general_clip0c(OPT_ARGS_NUM);
double opt_general_clip0d(OPT_ARGS_NUM);
double opt_general_clip1a(OPT_ARGS_NUM);
double opt_general_clip1b(OPT_ARGS_NUM);
double opt_general_clip1c(OPT_ARGS_NUM);
double opt_general_clip1d(OPT_ARGS_NUM);
double opt_general_clip2a(OPT_ARGS_NUM);
double opt_general_clip2b(OPT_ARGS_NUM);
double opt_general_clip2c(OPT_ARGS_NUM);
double opt_general_clip2d(OPT_ARGS_NUM);
double opt_general_clip3a(OPT_ARGS_NUM);
double opt_general_clip3b(OPT_ARGS_NUM);
double opt_general_clip3c(OPT_ARGS_NUM);
double opt_general_clip3d(OPT_ARGS_NUM);
double opt_general_clip4a(OPT_ARGS_NUM);
double opt_general_clip4b(OPT_ARGS_NUM);
double opt_general_clip4c(OPT_ARGS_NUM);
double opt_general_clip4d(OPT_ARGS_NUM);
double opt_general_clip5a(OPT_ARGS_NUM);
double opt_general_clip5b(OPT_ARGS_NUM);
double opt_general_clip5c(OPT_ARGS_NUM);
double opt_general_clip5d(OPT_ARGS_NUM);
double opt_general_clip_whole_elements(OPT_ARGS_NUM);
double opt_general_clip_only_draw_intersecting_volume(OPT_ARGS_NUM);
double opt_general_clip_only_volume(OPT_ARGS_NUM);
double opt_general_light0(OPT_ARGS_NUM);
double opt_general_light00(OPT_ARGS_NUM);
double opt_general_light01(OPT_ARGS_NUM);
double opt_general_light02(OPT_ARGS_NUM);
double opt_general_light03(OPT_ARGS_NUM);
double opt_general_light1(OPT_ARGS_NUM);
double opt_general_light10(OPT_ARGS_NUM);
double opt_general_light11(OPT_ARGS_NUM);
double opt_general_light12(OPT_ARGS_NUM);
double opt_general_light13(OPT_ARGS_NUM);
double opt_general_light2(OPT_ARGS_NUM);
double opt_general_light20(OPT_ARGS_NUM);
double opt_general_light21(OPT_ARGS_NUM);
double opt_general_light22(OPT_ARGS_NUM);
double opt_general_light23(OPT_ARGS_NUM);
double opt_general_light3(OPT_ARGS_NUM);
double opt_general_light30(OPT_ARGS_NUM);
double opt_general_light31(OPT_ARGS_NUM);
double opt_general_light32(OPT_ARGS_NUM);
double opt_general_light33(OPT_ARGS_NUM);
double opt_general_light4(OPT_ARGS_NUM);
double opt_general_light40(OPT_ARGS_NUM);
double opt_general_light41(OPT_ARGS_NUM);
double opt_general_light42(OPT_ARGS_NUM);
double opt_general_light43(OPT_ARGS_NUM);
double opt_general_light5(OPT_ARGS_NUM);
double opt_general_light50(OPT_ARGS_NUM);
double opt_general_light51(OPT_ARGS_NUM);
double opt_general_light52(OPT_ARGS_NUM);
double opt_general_light53(OPT_ARGS_NUM);
double opt_general_num_threads(OPT_ARGS_NUM);
double opt_geometry_transform(OPT_ARGS_NUM);
double opt_geometry_transform00(OPT_ARGS_NUM);
double opt_geometry_transform01(OPT_ARGS_NUM);
double opt_geometry_transform02(OPT_ARGS_NUM);
double opt_geometry_transform10(OPT_ARGS_NUM);
double opt_geometry_transform11(OPT_ARGS_NUM);
double opt_geometry_transform12(OPT_ARGS_NUM);
double opt_geometry_transform20(OPT_ARGS_NUM);
double opt_geometry_transform21(OPT_ARGS_NUM);
double opt_geometry_transform22(OPT_ARGS_NUM);
double opt_geometry_offset0(OPT_ARGS_NUM);
double opt_geometry_offset1(OPT_ARGS_NUM);
double opt_geometry_offset2(OPT_ARGS_NUM);
double opt_geometry_auto_coherence(OPT_ARGS_NUM);
double opt_geometry_oriented_physicals(OPT_ARGS_NUM);
double opt_geometry_highlight_orphans(OPT_ARGS_NUM);
double opt_geometry_tolerance(OPT_ARGS_NUM);
double opt_geometry_tolerance_boolean(OPT_ARGS_NUM);
double opt_geometry_normals(OPT_ARGS_NUM);
double opt_geometry_tangents(OPT_ARGS_NUM);
double opt_geometry_points(OPT_ARGS_NUM);
double opt_geometry_lines(OPT_ARGS_NUM);
double opt_geometry_surfaces(OPT_ARGS_NUM);
double opt_geometry_volumes(OPT_ARGS_NUM);
double opt_geometry_points_num(OPT_ARGS_NUM);
double opt_geometry_lines_num(OPT_ARGS_NUM);
double opt_geometry_surfaces_num(OPT_ARGS_NUM);
double opt_geometry_volumes_num(OPT_ARGS_NUM);
double opt_geometry_label_type(OPT_ARGS_NUM);
double opt_geometry_point_size(OPT_ARGS_NUM);
double opt_geometry_point_sel_size(OPT_ARGS_NUM);
double opt_geometry_point_type(OPT_ARGS_NUM);
double opt_geometry_reparam_on_face_robust(OPT_ARGS_NUM);
double opt_geometry_line_width(OPT_ARGS_NUM);
double opt_geometry_line_sel_width(OPT_ARGS_NUM);
double opt_geometry_line_type(OPT_ARGS_NUM);
double opt_geometry_surface_type(OPT_ARGS_NUM);
double opt_geometry_light(OPT_ARGS_NUM);
double opt_geometry_light_two_side(OPT_ARGS_NUM);
double opt_geometry_occ_auto_fix(OPT_ARGS_NUM);
double opt_geometry_occ_fix_degenerated(OPT_ARGS_NUM);
double opt_geometry_occ_fix_small_edges(OPT_ARGS_NUM);
double opt_geometry_occ_fix_small_faces(OPT_ARGS_NUM);
double opt_geometry_occ_sew_faces(OPT_ARGS_NUM);
double opt_geometry_occ_parallel(OPT_ARGS_NUM);
double opt_geometry_occ_boolean_preserve_numbering(OPT_ARGS_NUM);
double opt_geometry_occ_scaling(OPT_ARGS_NUM);
double opt_geometry_old_circle(OPT_ARGS_NUM);
double opt_geometry_old_newreg(OPT_ARGS_NUM);
double opt_geometry_old_ruled_surface(OPT_ARGS_NUM);
double opt_geometry_num_sub_edges(OPT_ARGS_NUM);
double opt_geometry_extrude_spline_points(OPT_ARGS_NUM);
double opt_geometry_extrude_return_lateral(OPT_ARGS_NUM);
double opt_geometry_scaling_factor(OPT_ARGS_NUM);
double opt_geometry_snap0(OPT_ARGS_NUM);
double opt_geometry_snap1(OPT_ARGS_NUM);
double opt_geometry_snap2(OPT_ARGS_NUM);
double opt_geometry_clip(OPT_ARGS_NUM);
double opt_geometry_copy_meshing_method(OPT_ARGS_NUM);
double opt_geometry_double_clicked_entity_tag(OPT_ARGS_NUM);
double opt_geometry_exact_extrusion(OPT_ARGS_NUM);
double opt_geometry_match_geom_and_mesh(OPT_ARGS_NUM);
double opt_mesh_label_sampling(OPT_ARGS_NUM);
double opt_mesh_optimize(OPT_ARGS_NUM);
double opt_mesh_optimize_threshold(OPT_ARGS_NUM);
double opt_mesh_optimize_netgen(OPT_ARGS_NUM);
double opt_mesh_old_refinement(OPT_ARGS_NUM);
double opt_mesh_refine_steps(OPT_ARGS_NUM);
double opt_mesh_normals(OPT_ARGS_NUM);
double opt_mesh_num_sub_edges(OPT_ARGS_NUM);
double opt_mesh_tangents(OPT_ARGS_NUM);
double opt_mesh_explode(OPT_ARGS_NUM);
double opt_mesh_scaling_factor(OPT_ARGS_NUM);
double opt_mesh_lc_min(OPT_ARGS_NUM);
double opt_mesh_lc_max(OPT_ARGS_NUM);
double opt_mesh_tolerance_edge_length(OPT_ARGS_NUM);
double opt_mesh_tolerance_initial_delaunay(OPT_ARGS_NUM);
double opt_mesh_lc_factor(OPT_ARGS_NUM);
double opt_mesh_lc_from_curvature(OPT_ARGS_NUM);
double opt_mesh_lc_from_points(OPT_ARGS_NUM);
double opt_mesh_lc_extend_from_boundary(OPT_ARGS_NUM);
double opt_mesh_lc_integration_precision(OPT_ARGS_NUM);
double opt_mesh_rand_factor(OPT_ARGS_NUM);
double opt_mesh_quality_inf(OPT_ARGS_NUM);
double opt_mesh_quality_sup(OPT_ARGS_NUM);
double opt_mesh_quality_type(OPT_ARGS_NUM);
double opt_mesh_radius_inf(OPT_ARGS_NUM);
double opt_mesh_radius_sup(OPT_ARGS_NUM);
double opt_mesh_label_type(OPT_ARGS_NUM);
double opt_mesh_points(OPT_ARGS_NUM);
double opt_mesh_lines(OPT_ARGS_NUM);
double opt_mesh_triangles(OPT_ARGS_NUM);
double opt_mesh_quadrangles(OPT_ARGS_NUM);
double opt_mesh_tetrahedra(OPT_ARGS_NUM);
double opt_mesh_hexahedra(OPT_ARGS_NUM);
double opt_mesh_prisms(OPT_ARGS_NUM);
double opt_mesh_pyramids(OPT_ARGS_NUM);
double opt_mesh_trihedra(OPT_ARGS_NUM);
double opt_mesh_surfaces_edges(OPT_ARGS_NUM);
double opt_mesh_surfaces_faces(OPT_ARGS_NUM);
double opt_mesh_volumes_edges(OPT_ARGS_NUM);
double opt_mesh_volumes_faces(OPT_ARGS_NUM);
double opt_mesh_points_num(OPT_ARGS_NUM);
double opt_mesh_lines_num(OPT_ARGS_NUM);
double opt_mesh_surfaces_num(OPT_ARGS_NUM);
double opt_mesh_volumes_num(OPT_ARGS_NUM);
double opt_mesh_point_size(OPT_ARGS_NUM);
double opt_mesh_point_type(OPT_ARGS_NUM);
double opt_mesh_line_width(OPT_ARGS_NUM);
double opt_mesh_smooth_normals(OPT_ARGS_NUM);
double opt_mesh_smooth_ratio(OPT_ARGS_NUM);
double opt_mesh_angle_smooth_normals(OPT_ARGS_NUM);
double opt_mesh_aniso_max(OPT_ARGS_NUM);
double opt_mesh_light(OPT_ARGS_NUM);
double opt_mesh_light_lines(OPT_ARGS_NUM);
double opt_mesh_light_two_side(OPT_ARGS_NUM);
double opt_mesh_file_format(OPT_ARGS_NUM);
double opt_mesh_newton_convergence_test_xyz(OPT_ARGS_NUM);
double opt_mesh_msh_file_version(OPT_ARGS_NUM);
double opt_mesh_msh_file_partitioned(OPT_ARGS_NUM);
double opt_mesh_msh_file_partitioned_topology(OPT_ARGS_NUM);
double opt_mesh_partition_hex_weight(OPT_ARGS_NUM);
double opt_mesh_partition_pri_weight(OPT_ARGS_NUM);
double opt_mesh_partition_pyr_weight(OPT_ARGS_NUM);
double opt_mesh_partition_trih_weight(OPT_ARGS_NUM);
double opt_mesh_partition_qua_weight(OPT_ARGS_NUM);
double opt_mesh_partition_tet_weight(OPT_ARGS_NUM);
double opt_mesh_partition_tri_weight(OPT_ARGS_NUM);
double opt_mesh_partition_boundaries(OPT_ARGS_NUM);
double opt_mesh_binary(OPT_ARGS_NUM);
double opt_mesh_lloyd(OPT_ARGS_NUM);
double opt_mesh_smooth_cross_field(OPT_ARGS_NUM);
double opt_mesh_bdf_field_format(OPT_ARGS_NUM);
double opt_mesh_nb_smoothing(OPT_ARGS_NUM);
double opt_mesh_algo2d(OPT_ARGS_NUM);
double opt_mesh_algo3d(OPT_ARGS_NUM);
double opt_mesh_algo_recombine(OPT_ARGS_NUM);
double opt_mesh_recombine_all(OPT_ARGS_NUM);
double opt_mesh_recombine3d_all(OPT_ARGS_NUM);
double opt_mesh_recombine3d_level(OPT_ARGS_NUM);
double opt_mesh_recombine3d_conformity(OPT_ARGS_NUM);
double opt_mesh_flexible_transfinite(OPT_ARGS_NUM);
double opt_mesh_do_recombination_test(OPT_ARGS_NUM);
double opt_mesh_recombination_test_start(OPT_ARGS_NUM);
double opt_mesh_recombination_no_greedy_strat(OPT_ARGS_NUM);
double opt_mesh_remesh_algo(OPT_ARGS_NUM);
double opt_mesh_remesh_param(OPT_ARGS_NUM);
double opt_mesh_algo_subdivide(OPT_ARGS_NUM);
double opt_mesh_mesh_only_visible(OPT_ARGS_NUM);
double opt_mesh_min_circ_points(OPT_ARGS_NUM);
double opt_mesh_allow_swap_edge_angle(OPT_ARGS_NUM);
double opt_mesh_min_curv_points(OPT_ARGS_NUM);
double opt_mesh_order(OPT_ARGS_NUM);
double opt_mesh_ho_optimize(OPT_ARGS_NUM);
double opt_mesh_ho_nlayers(OPT_ARGS_NUM);
double opt_mesh_ho_threshold_min(OPT_ARGS_NUM);
double opt_mesh_ho_threshold_max(OPT_ARGS_NUM);
double opt_mesh_ho_poisson(OPT_ARGS_NUM);
double opt_mesh_ho_opt_prim_surf_mesh(OPT_ARGS_NUM);
double opt_mesh_second_order_experimental(OPT_ARGS_NUM);
double opt_mesh_second_order_linear(OPT_ARGS_NUM);
double opt_mesh_second_order_incomplete(OPT_ARGS_NUM);
double opt_mesh_cgns_import_order(OPT_ARGS_NUM);
double opt_mesh_dual(OPT_ARGS_NUM);
double opt_mesh_voronoi(OPT_ARGS_NUM);
double opt_mesh_draw_skin_only(OPT_ARGS_NUM);
double opt_mesh_save_all(OPT_ARGS_NUM);
double opt_mesh_save_element_tag_type(OPT_ARGS_NUM);
double opt_mesh_save_parametric(OPT_ARGS_NUM);
double opt_mesh_save_topology(OPT_ARGS_NUM);
double opt_mesh_save_groups_of_nodes(OPT_ARGS_NUM);
double opt_mesh_color_carousel(OPT_ARGS_NUM);
double opt_mesh_switch_elem_tags(OPT_ARGS_NUM);
double opt_mesh_zone_definition(OPT_ARGS_NUM);
double opt_mesh_nb_nodes(OPT_ARGS_NUM);
double opt_mesh_nb_triangles(OPT_ARGS_NUM);
double opt_mesh_nb_quadrangles(OPT_ARGS_NUM);
double opt_mesh_nb_tetrahedra(OPT_ARGS_NUM);
double opt_mesh_nb_hexahedra(OPT_ARGS_NUM);
double opt_mesh_nb_prisms(OPT_ARGS_NUM);
double opt_mesh_nb_pyramids(OPT_ARGS_NUM);
double opt_mesh_nb_trihedra(OPT_ARGS_NUM);
double opt_mesh_cpu_time(OPT_ARGS_NUM);
double opt_mesh_partition_num(OPT_ARGS_NUM);
double opt_mesh_partition_metis_algorithm(OPT_ARGS_NUM);
double opt_mesh_partition_metis_edge_matching(OPT_ARGS_NUM);
double opt_mesh_partition_metis_refine_algorithm(OPT_ARGS_NUM);
double opt_mesh_clip(OPT_ARGS_NUM);
double opt_mesh_ignore_periodicity(OPT_ARGS_NUM);
double opt_mesh_preserve_numbering_msh2(OPT_ARGS_NUM);
double opt_mesh_max_num_threads_1d(OPT_ARGS_NUM);
double opt_mesh_max_num_threads_2d(OPT_ARGS_NUM);
double opt_mesh_max_num_threads_3d(OPT_ARGS_NUM);
double opt_solver_listen(OPT_ARGS_NUM);
double opt_solver_timeout(OPT_ARGS_NUM);
double opt_solver_plugins(OPT_ARGS_NUM);
double opt_solver_auto_load_database(OPT_ARGS_NUM);
double opt_solver_auto_save_database(OPT_ARGS_NUM);
double opt_solver_auto_archive_output_files(OPT_ARGS_NUM);
double opt_solver_auto_check(OPT_ARGS_NUM);
double opt_solver_auto_mesh(OPT_ARGS_NUM);
double opt_solver_auto_merge_file(OPT_ARGS_NUM);
double opt_solver_auto_show_views(OPT_ARGS_NUM);
double opt_solver_auto_show_last_step(OPT_ARGS_NUM);
double opt_solver_show_invisible_parameters(OPT_ARGS_NUM);
double opt_post_horizontal_scales(OPT_ARGS_NUM);
double opt_post_link(OPT_ARGS_NUM);
double opt_post_smooth(OPT_ARGS_NUM);
double opt_post_anim_delay(OPT_ARGS_NUM);
double opt_post_anim_cycle(OPT_ARGS_NUM);
double opt_post_anim_step(OPT_ARGS_NUM);
double opt_post_combine_remove_orig(OPT_ARGS_NUM);
double opt_post_plugins(OPT_ARGS_NUM);
double opt_post_nb_views(OPT_ARGS_NUM);
double opt_post_file_format(OPT_ARGS_NUM);
double opt_post_force_node_data(OPT_ARGS_NUM);
double opt_post_force_element_data(OPT_ARGS_NUM);
double opt_post_save_mesh(OPT_ARGS_NUM);
double opt_post_save_interpolation_matrices(OPT_ARGS_NUM);
double opt_post_double_clicked_graph_point_x(OPT_ARGS_NUM);
double opt_post_double_clicked_graph_point_y(OPT_ARGS_NUM);
double opt_post_double_clicked_view(OPT_ARGS_NUM);
double opt_view_nb_timestep(OPT_ARGS_NUM);
double opt_view_nb_non_empty_timestep(OPT_ARGS_NUM);
double opt_view_timestep(OPT_ARGS_NUM);
double opt_view_time(OPT_ARGS_NUM);
double opt_view_min(OPT_ARGS_NUM);
double opt_view_max(OPT_ARGS_NUM);
double opt_view_min_visible(OPT_ARGS_NUM);
double opt_view_max_visible(OPT_ARGS_NUM);
double opt_view_custom_min(OPT_ARGS_NUM);
double opt_view_custom_max(OPT_ARGS_NUM);
double opt_view_custom_abscissa_min(OPT_ARGS_NUM);
double opt_view_custom_abscissa_max(OPT_ARGS_NUM);
double opt_view_xmin(OPT_ARGS_NUM);
double opt_view_xmax(OPT_ARGS_NUM);
double opt_view_ymin(OPT_ARGS_NUM);
double opt_view_ymax(OPT_ARGS_NUM);
double opt_view_zmin(OPT_ARGS_NUM);
double opt_view_zmax(OPT_ARGS_NUM);
double opt_view_offset0(OPT_ARGS_NUM);
double opt_view_offset1(OPT_ARGS_NUM);
double opt_view_offset2(OPT_ARGS_NUM);
double opt_view_raise0(OPT_ARGS_NUM);
double opt_view_raise1(OPT_ARGS_NUM);
double opt_view_raise2(OPT_ARGS_NUM);
double opt_view_normal_raise(OPT_ARGS_NUM);
double opt_view_transform00(OPT_ARGS_NUM);
double opt_view_transform01(OPT_ARGS_NUM);
double opt_view_transform02(OPT_ARGS_NUM);
double opt_view_transform10(OPT_ARGS_NUM);
double opt_view_transform11(OPT_ARGS_NUM);
double opt_view_transform12(OPT_ARGS_NUM);
double opt_view_transform20(OPT_ARGS_NUM);
double opt_view_transform21(OPT_ARGS_NUM);
double opt_view_transform22(OPT_ARGS_NUM);
double opt_view_arrow_size_min(OPT_ARGS_NUM);
double opt_view_arrow_size_max(OPT_ARGS_NUM);
double opt_view_normals(OPT_ARGS_NUM);
double opt_view_tangents(OPT_ARGS_NUM);
double opt_view_displacement_factor(OPT_ARGS_NUM);
double opt_view_fake_transparency(OPT_ARGS_NUM);
double opt_view_use_stipple(OPT_ARGS_NUM);
double opt_view_explode(OPT_ARGS_NUM);
double opt_view_visible(OPT_ARGS_NUM);
double opt_view_intervals_type(OPT_ARGS_NUM);
double opt_view_saturate_values(OPT_ARGS_NUM);
double opt_view_max_recursion_level(OPT_ARGS_NUM);
double opt_view_adapt_visualization_grid(OPT_ARGS_NUM);
double opt_view_target_error(OPT_ARGS_NUM);
double opt_view_colormap_alpha(OPT_ARGS_NUM);
double opt_view_colormap_alpha_power(OPT_ARGS_NUM);
double opt_view_colormap_beta(OPT_ARGS_NUM);
double opt_view_colormap_bias(OPT_ARGS_NUM);
double opt_view_colormap_curvature(OPT_ARGS_NUM);
double opt_view_colormap_invert(OPT_ARGS_NUM);
double opt_view_colormap_number(OPT_ARGS_NUM);
double opt_view_colormap_rotation(OPT_ARGS_NUM);
double opt_view_colormap_swap(OPT_ARGS_NUM);
double opt_view_external_view(OPT_ARGS_NUM);
double opt_view_gen_raise_view(OPT_ARGS_NUM);
double opt_view_gen_raise_factor(OPT_ARGS_NUM);
double opt_view_use_gen_raise(OPT_ARGS_NUM);
double opt_view_type(OPT_ARGS_NUM);
double opt_view_axes(OPT_ARGS_NUM);
double opt_view_axes_mikado(OPT_ARGS_NUM);
double opt_view_axes_auto_position(OPT_ARGS_NUM);
double opt_view_axes_tics0(OPT_ARGS_NUM);
double opt_view_axes_tics1(OPT_ARGS_NUM);
double opt_view_axes_tics2(OPT_ARGS_NUM);
double opt_view_axes_xmin(OPT_ARGS_NUM);
double opt_view_axes_ymin(OPT_ARGS_NUM);
double opt_view_axes_zmin(OPT_ARGS_NUM);
double opt_view_axes_xmax(OPT_ARGS_NUM);
double opt_view_axes_ymax(OPT_ARGS_NUM);
double opt_view_axes_zmax(OPT_ARGS_NUM);
double opt_view_position0(OPT_ARGS_NUM);
double opt_view_position1(OPT_ARGS_NUM);
double opt_view_auto_position(OPT_ARGS_NUM);
double opt_view_sampling(OPT_ARGS_NUM);
double opt_view_size0(OPT_ARGS_NUM);
double opt_view_size1(OPT_ARGS_NUM);
double opt_view_nb_iso(OPT_ARGS_NUM);
double opt_view_boundary(OPT_ARGS_NUM);
double opt_view_light(OPT_ARGS_NUM);
double opt_view_light_two_side(OPT_ARGS_NUM);
double opt_view_light_lines(OPT_ARGS_NUM);
double opt_view_smooth_normals(OPT_ARGS_NUM);
double opt_view_angle_smooth_normals(OPT_ARGS_NUM);
double opt_view_show_element(OPT_ARGS_NUM);
double opt_view_show_time(OPT_ARGS_NUM);
double opt_view_show_scale(OPT_ARGS_NUM);
double opt_view_draw_strings(OPT_ARGS_NUM);
double opt_view_draw_points(OPT_ARGS_NUM);
double opt_view_draw_quadrangles(OPT_ARGS_NUM);
double opt_view_draw_lines(OPT_ARGS_NUM);
double opt_view_draw_triangles(OPT_ARGS_NUM);
double opt_view_draw_tetrahedra(OPT_ARGS_NUM);
double opt_view_draw_hexahedra(OPT_ARGS_NUM);
double opt_view_draw_prisms(OPT_ARGS_NUM);
double opt_view_draw_pyramids(OPT_ARGS_NUM);
double opt_view_draw_trihedra(OPT_ARGS_NUM);
double opt_view_draw_scalars(OPT_ARGS_NUM);
double opt_view_draw_vectors(OPT_ARGS_NUM);
double opt_view_draw_tensors(OPT_ARGS_NUM);
double opt_view_draw_skin_only(OPT_ARGS_NUM);
double opt_view_scale_type(OPT_ARGS_NUM);
double opt_view_tensor_type(OPT_ARGS_NUM);
double opt_view_range_type(OPT_ARGS_NUM);
double opt_view_abscissa_range_type(OPT_ARGS_NUM);
double opt_view_vector_type(OPT_ARGS_NUM);
double opt_view_glyph_location(OPT_ARGS_NUM);
double opt_view_center_glyphs(OPT_ARGS_NUM);
double opt_view_point_size(OPT_ARGS_NUM);
double opt_view_line_width(OPT_ARGS_NUM);
double opt_view_point_type(OPT_ARGS_NUM);
double opt_view_line_type(OPT_ARGS_NUM);
double opt_view_clip(OPT_ARGS_NUM);
double opt_view_force_num_components(OPT_ARGS_NUM);
double opt_view_component_map0(OPT_ARGS_NUM);
double opt_view_component_map1(OPT_ARGS_NUM);
double opt_view_component_map2(OPT_ARGS_NUM);
double opt_view_component_map3(OPT_ARGS_NUM);
double opt_view_component_map4(OPT_ARGS_NUM);
double opt_view_component_map5(OPT_ARGS_NUM);
double opt_view_component_map6(OPT_ARGS_NUM);
double opt_view_component_map7(OPT_ARGS_NUM);
double opt_view_component_map8(OPT_ARGS_NUM);
double opt_view_closed(OPT_ARGS_NUM);
double opt_print_file_format(OPT_ARGS_NUM);
double opt_print_eps_compress(OPT_ARGS_NUM);
double opt_print_eps_ps3shading(OPT_ARGS_NUM);
double opt_print_eps_quality(OPT_ARGS_NUM);
double opt_print_eps_occlusion_culling(OPT_ARGS_NUM);
double opt_print_eps_best_root(OPT_ARGS_NUM);
double opt_print_eps_line_width_factor(OPT_ARGS_NUM);
double opt_print_eps_point_size_factor(OPT_ARGS_NUM);
double opt_print_jpeg_quality(OPT_ARGS_NUM);
double opt_print_jpeg_smoothing(OPT_ARGS_NUM);
double opt_print_geo_labels(OPT_ARGS_NUM);
double opt_print_geo_only_physicals(OPT_ARGS_NUM);
double opt_print_pos_elementary(OPT_ARGS_NUM);
double opt_print_pos_element(OPT_ARGS_NUM);
double opt_print_pos_gamma(OPT_ARGS_NUM);
double opt_print_pos_eta(OPT_ARGS_NUM);
double opt_print_pos_SICN(OPT_ARGS_NUM);
double opt_print_pos_SIGE(OPT_ARGS_NUM);
double opt_print_pos_disto(OPT_ARGS_NUM);
double opt_print_gif_dither(OPT_ARGS_NUM);
double opt_print_gif_sort(OPT_ARGS_NUM);
double opt_print_gif_interlace(OPT_ARGS_NUM);
double opt_print_gif_transparent(OPT_ARGS_NUM);
double opt_print_background(OPT_ARGS_NUM);
double opt_print_pgf_two_dim(OPT_ARGS_NUM);
double opt_print_pgf_export_axis(OPT_ARGS_NUM);
double opt_print_pgf_horiz_bar(OPT_ARGS_NUM);
double opt_print_text(OPT_ARGS_NUM);
double opt_print_tex_as_equation(OPT_ARGS_NUM);
double opt_print_composite_windows(OPT_ARGS_NUM);
double opt_print_delete_tmp_files(OPT_ARGS_NUM);
double opt_print_height(OPT_ARGS_NUM);
double opt_print_width(OPT_ARGS_NUM);
double opt_print_parameter(OPT_ARGS_NUM);
double opt_print_parameter_first(OPT_ARGS_NUM);
double opt_print_parameter_last(OPT_ARGS_NUM);
double opt_print_parameter_steps(OPT_ARGS_NUM);
double opt_print_x3d_compatibility(OPT_ARGS_NUM);
double opt_print_x3d_transparency(OPT_ARGS_NUM);
double opt_print_x3d_remove_inner_borders(OPT_ARGS_NUM);
double opt_print_x3d_precision(OPT_ARGS_NUM);

// COLORS

unsigned int opt_general_color_background(OPT_ARGS_COL);
unsigned int opt_general_color_background_gradient(OPT_ARGS_COL);
unsigned int opt_general_color_foreground(OPT_ARGS_COL);
unsigned int opt_general_color_text(OPT_ARGS_COL);
unsigned int opt_general_color_axes(OPT_ARGS_COL);
unsigned int opt_general_color_small_axes(OPT_ARGS_COL);
unsigned int opt_general_color_ambient_light(OPT_ARGS_COL);
unsigned int opt_general_color_diffuse_light(OPT_ARGS_COL);
unsigned int opt_general_color_specular_light(OPT_ARGS_COL);
unsigned int opt_geometry_color_points(OPT_ARGS_COL);
unsigned int opt_geometry_color_lines(OPT_ARGS_COL);
unsigned int opt_geometry_color_surfaces(OPT_ARGS_COL);
unsigned int opt_geometry_color_volumes(OPT_ARGS_COL);
unsigned int opt_geometry_color_selection(OPT_ARGS_COL);
unsigned int opt_geometry_color_highlight0(OPT_ARGS_COL);
unsigned int opt_geometry_color_highlight1(OPT_ARGS_COL);
unsigned int opt_geometry_color_highlight2(OPT_ARGS_COL);
unsigned int opt_geometry_color_tangents(OPT_ARGS_COL);
unsigned int opt_geometry_color_normals(OPT_ARGS_COL);
unsigned int opt_geometry_color_projection(OPT_ARGS_COL);
unsigned int opt_mesh_color_points(OPT_ARGS_COL);
unsigned int opt_mesh_color_points_sup(OPT_ARGS_COL);
unsigned int opt_mesh_color_lines(OPT_ARGS_COL);
unsigned int opt_mesh_color_triangles(OPT_ARGS_COL);
unsigned int opt_mesh_color_quadrangles(OPT_ARGS_COL);
unsigned int opt_mesh_color_tetrahedra(OPT_ARGS_COL);
unsigned int opt_mesh_color_hexahedra(OPT_ARGS_COL);
unsigned int opt_mesh_color_prisms(OPT_ARGS_COL);
unsigned int opt_mesh_color_pyramid(OPT_ARGS_COL);
unsigned int opt_mesh_color_trihedron(OPT_ARGS_COL);
unsigned int opt_mesh_color_tangents(OPT_ARGS_COL);
unsigned int opt_mesh_color_normals(OPT_ARGS_COL);
unsigned int opt_mesh_color_0(OPT_ARGS_COL);
unsigned int opt_mesh_color_1(OPT_ARGS_COL);
unsigned int opt_mesh_color_2(OPT_ARGS_COL);
unsigned int opt_mesh_color_3(OPT_ARGS_COL);
unsigned int opt_mesh_color_4(OPT_ARGS_COL);
unsigned int opt_mesh_color_5(OPT_ARGS_COL);
unsigned int opt_mesh_color_6(OPT_ARGS_COL);
unsigned int opt_mesh_color_7(OPT_ARGS_COL);
unsigned int opt_mesh_color_8(OPT_ARGS_COL);
unsigned int opt_mesh_color_9(OPT_ARGS_COL);
unsigned int opt_mesh_color_10(OPT_ARGS_COL);
unsigned int opt_mesh_color_11(OPT_ARGS_COL);
unsigned int opt_mesh_color_12(OPT_ARGS_COL);
unsigned int opt_mesh_color_13(OPT_ARGS_COL);
unsigned int opt_mesh_color_14(OPT_ARGS_COL);
unsigned int opt_mesh_color_15(OPT_ARGS_COL);
unsigned int opt_mesh_color_16(OPT_ARGS_COL);
unsigned int opt_mesh_color_17(OPT_ARGS_COL);
unsigned int opt_mesh_color_18(OPT_ARGS_COL);
unsigned int opt_mesh_color_19(OPT_ARGS_COL);
unsigned int opt_view_color_points(OPT_ARGS_COL);
unsigned int opt_view_color_lines(OPT_ARGS_COL);
unsigned int opt_view_color_triangles(OPT_ARGS_COL);
unsigned int opt_view_color_quadrangles(OPT_ARGS_COL);
unsigned int opt_view_color_tetrahedra(OPT_ARGS_COL);
unsigned int opt_view_color_hexahedra(OPT_ARGS_COL);
unsigned int opt_view_color_prisms(OPT_ARGS_COL);
unsigned int opt_view_color_pyramids(OPT_ARGS_COL);
unsigned int opt_view_color_trihedra(OPT_ARGS_COL);
unsigned int opt_view_color_tangents(OPT_ARGS_COL);
unsigned int opt_view_color_normals(OPT_ARGS_COL);
unsigned int opt_view_color_text2d(OPT_ARGS_COL);
unsigned int opt_view_color_text3d(OPT_ARGS_COL);
unsigned int opt_view_color_axes(OPT_ARGS_COL);
unsigned int opt_view_color_background2d(OPT_ARGS_COL);

// Data structures and global functions

typedef struct {
  const char *str ;
  int int1, int2, int3, int4 ;
} StringX4Int;

typedef struct {
  int level;
  const char *str;
  std::string (*function)(int num, int action, std::string val);
  std::string def;
  const char *help;
} StringXString;

typedef struct {
  int level;
  const char *str;
  double (*function)(int num, int action, double val);
  double def ;
  const char *help;
} StringXNumber;

typedef struct {
  int level;
  const char *str;
  unsigned int (*function)(int num, int action, unsigned int val);
  // the defaults are stored in individual bytes so that we can initialize
  // them statically independently of the machine endianness. They will be
  // packed into unsigned ints at runtime
  unsigned char def1[4], def2[4], def3[4], def4[4];
  const char *help;
} StringXColor;

void InitOptions(int num);
void InitOptionsGUI(int num);
void ReInitOptions(int num);
void PrintOptions(int num, int level, int diff, int help, const char *filename,
                  std::vector<std::string> *vec=0);
void PrintOptionsDoc();

bool StringOption(int action, const char *category, int num,
                  const char *name, std::string &val, bool warnIfUnknown=true);
bool NumberOption(int action, const char *category, int num,
                  const char *name, double &val, bool warnIfUnknown=true);
bool ColorOption(int action, const char *category, int num,
                 const char *name, unsigned int &val, bool warnIfUnknown=true);

GmshColorTable *GetColorTable(int num);
int GetColorForString(int alpha, const char *string, int *FlagError);
bool GetRGBForString(const char *string, int &r, int &g, int &b);

#endif
