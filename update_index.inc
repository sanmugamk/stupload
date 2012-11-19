<?php

	function update_index($params) {
		if($params){
			$path = drupal_get_path('module', 'stupload');
			drupal_add_js($path . '/stupload.js');
			drupal_add_css($path . '/stupload.css');

			$params = parse_url($params);
			$tr_data = explode('=', $params['query']);
			$trid = $tr_data[1];
			
			$query = "select td.id as tdid, td.foss_category, td.tutorial_name, td.tutorial_level, td.order_code, tr.language, tr.tutorial_outline, tr.tutorial_script, tr.tutorial_video, tcc.id as tccid, tcc.tutorial_slide, tcc.tutorial_code, tcc.tutorial_assignment from tutorial_details td ,tutorial_resources tr, tutorial_common_contents tcc where td.id=tr.tutorial_detail_id and tr.tutorial_content_id=tcc.id and tr.id='".$trid."'";

			$result = db_query($query);

			$content = db_fetch_object($result);

			// check if video exists ot not
			require_once('path.config.inc');

			if($content->tutorial_video != 'pending' && file_exists($GLOBALS['file_upload_path'].$content->tutorial_video)){
				//$video_url = $content->tutorial_video;
				$video_url = "<a href='".$tutorial_path.$content->tutorial_video."' target='_blank' >Accepted</a>";

			}else{
				$video_url = 'pending';
			}

			// check if slide exists ot not

			if($content->tutorial_slide != 'pending' && file_exists($GLOBALS['file_upload_path'].$content->tutorial_slide)){
				//$slide_url = $content->tutorial_slide;
				$slide_url = "<a href='".$tutorial_path.$content->tutorial_slide."' target='_blank'>Accepted</a>";
			}else{
				$slide_url = 'pending';
			}

			// check if codefile exists ot not

			if($content->tutorial_code != 'pending' && $content->tutorial_code != 'notrequired' && file_exists($GLOBALS['file_upload_path'].$content->tutorial_slide)){
				//$codefile_url = $content->tutorial_code;
				$codefile_url = "<a href='".$tutorial_path.$content->tutorial_code."' target='_blank'>Accepted</a>";
			}elseif($content->tutorial_code == 'notrequired'){
				$codefile_url = 'notrequired';
			}else{
				$codefile_url = 'pending';
			}

			// check if assignment exists ot not
			if($content->tutorial_assignment != 'pending' && $content->tutorial_assignment != 'notrequired' && file_exists($GLOBALS['file_upload_path'].$content->tutorial_assignment)){
				//$codefile_url = $content->tutorial_assignment;
				$assignment_url = "<a href='".$tutorial_path.$content->tutorial_assignment."' target='_blank'>Accepted</a>";
			}elseif($content->tutorial_assignment == 'notrequired'){
				$assignment_url = 'notrequired';
			}else{
				$assignment_url = 'pending';
			}
			
			


			$output = "<div class='stupload-form'>";
			$output .= "<table class='upload-index'>";
			$output .= "<tr><th class='title'>Title</th><th class='content'>Content</th><th class='update'>Update</th></tr>";
			$output .= "<tr><td class='title'>Foss Category</td><td class='content'>".$content->foss_category."</td><td class='update'></td></tr>";
			$output .= "<tr><td class='title'>Tutorial Name</td><td class='content'>".$content->tutorial_name."</td><td class='update'></td></tr>";
			$output .= "<tr><td class='title'>Tutorial Level</td><td class='content'>".$content->tutorial_level."</td><td class='update'></td></tr>";
			$output .= "<tr><td class='title'>Tutorial Language</td><td class='content'>".$content->language."</td><td class='update'></td></tr>";
			$output .= "<tr><td class='title'>Study Plan</td><td class='content'>".$content->order_code."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/studyplan' method='post'><input type='hidden' name='tdid' value='".$content->tdid."'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";
			$output .= "<tr><td class='title'>Tutorial Outline</td><td class='content'>".$content->tutorial_outline."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/outline' method='post'><input type='hidden' name='trid' value='".$trid."'><input type='hidden' name='outline' value='".$content->tutorial_outline."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "<tr><td class='title'>Tutorial Script</td><td class='content'>".$content->tutorial_script."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/script' method='post'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "<tr><td class='title'>Tutorial Video</td><td class='content'>".$video_url."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/video' method='post'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "<tr><td class='title'>Tutorial slide</td><td class='content'>".$slide_url."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/slide' method='post'><input type='hidden' name='tccid' value='".$content->tccid."'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "<tr><td class='title'>Tutorial Code</td><td class='content'>".$codefile_url."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/codefile' method='post'><input type='hidden' name='tccid' value='".$content->tccid."'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "<tr><td class='title'>Tutorial Assignment</td><td class='content'>".$assignment_url."</td><td class='update'><form action='".$GLOBALS['base_url']."/stupload/update/assignment' method='post'><input type='hidden' name='tccid' value='".$content->tccid."'><input type='hidden' name='trid' value='".$trid."'><input type='submit' value='Update'></form></td></tr>";

			$output .= "</table>";
			$output .= "</div>";

			return $output;
			

		}else{
			$output = "<p>Somthing went wrong. Please, try again</p>";
			return $output;

		}


	
	}
	

?>