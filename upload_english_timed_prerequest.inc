<?php

	function upload_english_timed_prerequest_form($form_state) {
		$path = drupal_get_path('module', 'stupload');
		drupal_add_js($path . '/stupload.js');
		drupal_add_css($path . '/stupload.css');

		$upload_option = array('Reqired' => 'Reqired', 'Not Reqired' => 'Not Reqired', 'Upload Later' => 'Upload Later');
		$tutorial_name = array('' => 'Tutorial Name');
		$query = "select * from foss_categories";
		$result = db_query($query);
		$foss_category = array('' => 'FOSS category');
		while($row = db_fetch_object($result)){
			$foss_category[$row->name] =  $row->name;
		}
		$form['#prefix'] = '<div class="stupload-form">';
		$form['#suffix'] = '</div>';
		$form['#attributes'] = array('enctype' => "multipart/form-data", 'class' => 'upload-english');
	
		$form['foss_category'] = array(
			'#type' => 'select',
			'#title' => t('FOSS Category Name'),
			'#required' => TRUE,
			'#options' => $foss_category,
			'#attributes' => array('class' => 'upeng_foss_category_name'),
			'#prefix' => '<div class="uenglish-category-level-name">',
		);
		$form['tutorial_level'] = array(
			'#type' => 'select',
			'#title' => t('Tutorial Level'),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#options' => array(''=> 'Level'),
			'#attributes' => array('class' => 'upeng_tutorial_level'),
			'#prefix' => '<div class="uenglish-level-name"><div class="uenglish-level">',
			'#suffix' => '</div>', 
		);
		$form['tutorial_name'] = array(
			'#type' => 'select',
			'#title' => t('Tutorial Name'),
			'#required' => TRUE,
			'#validated' => TRUE,
			'#options' => $tutorial_name,
			'#attributes' => array('class' => 'upeng_tutorial_name'),
			'#prefix' => '<div class="uenglish-name">',
			'#suffix' => '</div></div></div>', 
		);
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit')
	   );
	
	return $form;
	
	}
	
	
	function upload_english_timed_prerequest_form_validate($form, &$form_state){
		if($form_state['values']['tutorial_name'] != ''){
			$query = "select id from tutorial_details where foss_category='".$form_state['values']['foss_category']."' and tutorial_name='".$form_state['values']['tutorial_name']."' and tutorial_level='".$form_state['values']['tutorial_level']."'";

		$result = db_query($query);
		$row = db_fetch_object($result);
			$query = "select tutorial_detail_id from tutorial_resources where tutorial_detail_id='".$row->id."' and language='English'";
			$result = db_query($query);
			$row = db_fetch_object($result);
			if($row){
				form_set_error('tutorial_name', t('This Tutorial Already Exits.'));
			}
		}
		return;
	}
	
	function upload_english_timed_prerequest_form_submit($form, &$form_state){

		$query = "Select tr.tutorial_content_id, tr.tutorial_outline, tr.tutorial_video, tcc.tutorial_slide, tcc.tutorial_code, tcc.tutorial_assignment from tutorial_resources tr, tutorial_common_contents tcc, tutorial_details td where tcc.tutorial_detail_id=tr.tutorial_detail_id and ";
		if(db_query($query)){
			drupal_set_message('New FOSS Category Added Successfully');
			$query = "select id from tutorial_resources where tutorial_detail_id='".$tutorial_detail_id."' and language='".$language."'";
			$result = db_query($query);
			$row = db_fetch_object($result);
			$redirect = 'stupload/english_index/?tr='.$row->id;
			drupal_goto($path = $redirect, $query = NULL, $fragment = NULL, $http_response_code = 302);
		}else {
			drupal_set_message('Error while Adding Foss Category, Please try again.');
		}
		

}


?>