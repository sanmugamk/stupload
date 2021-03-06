<?php
	function upload_olang_video() {
		if($_REQUEST['trid']){

			$trid = $_REQUEST['trid'];
			$output = "<h2>Upload English Video for ".$_REQUEST['tn']."</h2>";
			$output .= drupal_get_form('upload_olang_video_form', $trid);
			return $output;
		}else{
			$output = "<p>Something went wrong. Please, try again.</p>";
			return $output;
		}

	}


	function upload_olang_video_form($form_state, $trid) {
		$path = drupal_get_path('module', 'stupload');
		drupal_add_js($path . '/stupload.js');
		drupal_add_css($path . '/stupload.css');
		$form['#prefix'] = '<div class="stupload-form">';
		$form['#suffix'] = '</div>';
		$form['#attributes'] = array('enctype' => "multipart/form-data", 'class' => 'addfoss');

		
		$form['trid'] = array(
			'#type' => 'hidden',
			'#value' => $trid,
		);

		$form['video_status'] = array(
			'#type' => 'select',
			'#title' => t('Slide Status'),
			'#required' => TRUE,
			'#options' => array(0 => 'Required' , 1 => 'Will upload later'),
			'#attributes' => array('class' => 'upeng_video_status'),
		);
		$form['video'] = array(
			'#type' => 'file',
			'#title' => t('Video <span class="upload-help-test"> (Upload .ogv file only)</span>'),
			'#attributes' => array('class' => 'upeng_video'),
			'#prefix' => '<div class="stupload-form-video">',
			'#suffix' => '</div>'
		);
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit')
	   );
	
	return $form;
	
	}
	
	
	function upload_olang_video_form_validate($form, &$form_state){
		if ($form_state['values']['video_status'] == 0){
			if($_FILES['files']['tmp_name']['video'] == ''){
				form_set_error('video', t('Please select the video file.'));
			}else{
				$file_ext = substr($_FILES['files']['name']['video'], strripos($_FILES['files']['name']['video'], '.')); // get file name
				$filesize = $_FILES['files']['size']['video'];
				$allowed_file_types = array('.ogv');
				if (!in_array($file_ext,$allowed_file_types)  &&  ($filesize < 80000000)) {
					form_set_error('video', t('Please select proper file. ogv files only allowed.'));
				}
			}
		}
		
	  	return;
	}
	
	function upload_olang_video_form_submit($form, &$form_state){
		// select Tutorial categoty
		global $user;
		$query = "select tr.language, td.foss_category, td.tutorial_name, td.tutorial_level from tutorial_resources tr INNER JOIN tutorial_details td ON td.id=tr.tutorial_detail_id where tr.id='".$form_state['values']['trid']."'";

		$result = db_query($query);
		$tutorial_detail = db_fetch_object($result);

		$video_path = 'st_videos/'.$tutorial_detail->foss_category.'/'.$tutorial_detail->tutorial_level.'/'.$tutorial_detail->tutorial_name.'/';
		require_once('path.config.inc');
		$path = $file_upload_path.$video_path;
		$file_ext = substr($_FILES['files']['name']['video'], strripos($_FILES['files']['name']['video'], '.'));
		$file_name = $tutorial_detail->tutorial_name.'-'.$tutorial_detail->language.$file_ext;
		if($form_state['values']['video_status'] == 1){
			$tutorial_video = 'pending';
			$query = "UPDATE tutorial_resources SET cvideo_version=1, tutorial_video='".$tutorial_video."' WHERE id='".$form_state['values']['trid']."'";
			db_query($query);
			// to track uploader
			$query = "INSERT INTO `tutorial_update_log` (`id`, `tutorial_resources_id`, `update_time`, `updated_by`, `updated_content`) VALUES (NULL, '".$form_state['values']['trid']."', CURRENT_TIMESTAMP, '".$user->name."', 'video')";

			if(db_query($query)){
				drupal_set_message('Tutorial Video Updated Successfully');
				$redirect = 'stupload/olang_index/?tr='.$form_state['values']['trid'];
				drupal_goto($path = $redirect, $query=NULL, $fragment = NULL, $http_response_code = 302);
			}else {
				drupal_set_message('Error while Adding Tutorial Video, Please try again.');
			}
		}
		if($_FILES['files']['size']['video'] > 0){
			if(move_uploaded_file($_FILES['files']['tmp_name']['video'], $path.$file_name)){
				$tutorial_video = $video_path.$file_name;
				// insert into common data table
				$query = "UPDATE tutorial_resources SET cvideo_version=1, tutorial_video='".$tutorial_video."' WHERE id='".$form_state['values']['trid']."'";
				db_query($query);
				// to track uploader
				$query = "INSERT INTO `tutorial_update_log` (`id`, `tutorial_resources_id`, `update_time`, `updated_by`, `updated_content`) VALUES (NULL, '".$form_state['values']['trid']."', CURRENT_TIMESTAMP, '".$user->name."', 'video')";

				if(db_query($query)){
					drupal_set_message('Tutorial Video Updated Successfully');
					$redirect = 'stupload/olang_index/?tr='.$form_state['values']['trid'];
					drupal_goto($path = $redirect, $query=NULL, $fragment = NULL, $http_response_code = 302);
				}else {
					drupal_set_message('Error while Adding Tutorial Video, Please try again.');
				}
			}else{
				drupal_set_message('Error while Uploading Video file, Please try again..');
			}

		}

}

?>
