$(document).ready(function(){
	webroot = "http://"+location.hostname+"/tester/stupload/";
	loading_image = "<img src='http://"+location.hostname+"/tester/ajax-loader.gif' />";
	wiki_url = "http://"+location.hostname+"/wiki/index.php/";
	// for add availabel tutorial levels for add tutorial names
	$('.add-new-tutorial-name').css({'display':'none'});
	$('.uptn_tutorial_level').change(function(){
		foss = $('.uptn_foss_category_name').val();
		level = $(this).val();
		$.ajax({
			type : 'POST',
			url : webroot + "get_tutorial_levels",
			data : {
				'foss' : foss, 'level' : level
			},
			beforeSend: function() {
			    field_data = $('.poll-form').html();
			    $('.poll-form').html(loading_image);
			    name_data = $('.aable-tutorial-name').html();
			    $('.aable-tutorial-name').html('');
			},
			success : function(data){
				output = JSON.parse(data);
				var html_data = "<option val=''>-- Select --</option>";
				var html_data2 = "<option val=''>-- Select --</option><option value=2>-- Add New Tutorial --</option>";
				if(output){
					$('.poll-form').html(field_data);
					// add levels
					for (var i=0; i < output['tlevels'].length; i++)
					{
						html_data += "<option value='"+ output['tlevels'][i] +"'>" + output['tlevels'][i] + "</option>";	
					}
					$('.uptn_tutorial_order_no').html(html_data);
					$('.aable-tutorial-name').html(name_data);
					if(output['tnames']){
						for (var i=0; i < output['tnames'].length; i++)
						{
							html_data2 += "<option value='"+ output['tnames'][i] +"'>" + output['tnames'][i] + "</option>";	
						}
					}
					$('.uptn_tutorial_avnames').html(html_data2);
					//show add new tutorial names
					$('.uptn_tutorial_avnames').change(function(){
						if($(this).val() == 2){
							$('.add-new-tutorial-name').css({'display':'block'});
						}else{
							$('.add-new-tutorial-name').css({'display':'none'});
						}
					});

				}else{
					alert('Somthing wrong, Please refresh page');
				}
			}
		});
	});
	$('.upeng_foss_category_name').change(function(){
		foss = $(this).val();
		$.ajax({
			type : 'POST',
			url : webroot + "get_category_levels",
			data : {
				'foss' : foss
			},
			beforeSend: function() {
			    field_data = $('.uenglish-level-name').html();
			    $('.uenglish-level-name').html(loading_image);
			},
			success : function(data){
				output = JSON.parse(data);
				var html_data = "<option value=''>-- Select --</option>";
				if(output){
					$('.uenglish-level-name').html(field_data);
					for (var i=0; i < output.length; i++)
					{
						html_data += "<option value='"+ output[i].tutorial_level +"'>" + output[i].tutorial_level + "</option>";	
					}
					console.log(html_data);
					$('.upeng_tutorial_level').html(html_data);
					// adding the tutorial name under tutorial level
					$('.upeng_tutorial_level').change(function(){
						level = $(this).val();
						foss = $('.upeng_foss_category_name').val();
						$.ajax({
							type : 'POST',
							url : webroot + "get_category_names",
							data : {
								'level' : level,
								'foss' : foss
							},
							beforeSend: function() {
							    field_data = $('.uenglish-name').html();
							    $('.uenglish-name').html(loading_image);
							},
							success : function(data){
								output = JSON.parse(data);
								var html_data = "<option value=''>-- Select --</option>";
								if(output){
									$('.uenglish-name').html(field_data);
									for (var i=0; i < output.length; i++)
									{
										html_data += "<option value='"+ output[i].tutorial_name +"'>" + output[i].tutorial_name + "</option>";	
									}
									console.log(html_data);
									$('.upeng_tutorial_name').html(html_data);
								}else{
									alert('Somthing wrong, Please refresh page');
								}
							}
						});
					});
				}else{
					alert('Somthing wrong, Please refresh page');
				}
			}
		});
	});
	$('.upeng_timed_foss_category_name').change(function(){
		foss = $(this).val();
		$.ajax({
			type : 'POST',
			url : webroot + "get_category_levels",
			data : {
				'foss' : foss
			},
			beforeSend: function() {
			    field_data = $('.uenglish-timed-level-name').html();
			    $('.uenglish-timed-level-name').html(loading_image);
			},
			success : function(data){
				output = JSON.parse(data);
				var html_data = "<option value=''>-- Select --</option>";
				if(output){
					$('.uenglish-timed-level-name').html(field_data);
					for (var i=0; i < output.length; i++)
					{
						html_data += "<option value='"+ output[i].tutorial_level +"'>" + output[i].tutorial_level + "</option>";	
					}
					console.log(html_data);
					$('.upeng_timed_tutorial_level').html(html_data);
					// adding the tutorial name under tutorial level
					$('.upeng_timed_tutorial_level').change(function(){
						level = $(this).val();
						foss = $('.upeng_timed_foss_category_name').val();
						$.ajax({
							type : 'POST',
							url : webroot + "get_timed_category_names",
							data : {
								'level' : level,
								'foss' : foss
							},
							beforeSend: function() {
							    field_data = $('.uenglish-timed-name').html();
							    $('.uenglish-timed-name').html(loading_image);
							},
							success : function(data){
								output = JSON.parse(data);
								var html_data = "<option value=''>-- Select --</option>";
								if(output){
									$('.uenglish-timed-name').html(field_data);
									for (var i=0; i < output.length; i++)
									{
										html_data += "<option value='"+ output[i].tutorial_name +"'>" + output[i].tutorial_name + "</option>";	
									}
									console.log(html_data);
									$('.upeng_timed_tutorial_name').html(html_data);
								}else{
									alert('Somthing wrong, Please refresh page');
								}
							}
						});
					});
				}else{
					alert('Somthing wrong, Please refresh page');
				}
			}
		});
	});
	// field hide and show
	if($('.uptn_outline_status').val() == 0){
		$('div.stupload-outline').css({'display' : 'block'});
	}
	$('.uptn_outline_status').change(function(){
		if($(this).val() == 0){
			$('div.stupload-outline').css({'display' : 'block'});
		}else{
			$('div.stupload-outline').css({'display' : 'none'});
		}
	});

	// for script file
	path = $('.upeng_script_wiki').val();
	wiki_data = "<iframe width='100%' height='600px' src='"+wiki_url+path+"'></iframe>";
	if($('.upeng_script_status').val() == 0){
		$('div.wiki-script-file').html(wiki_data);
	}
	$('.upeng_script_status').change(function(){
		if($(this).val() == 0){
			$('div.wiki-script-file').html(wiki_data);
		}else{
			$('div.wiki-script-file').html('<p></p>');
		}
	});
	// for slide file
	if($('.upeng_slide_status').val() == 0){
		$('div.stupload-form-slide').css({'display' : 'block'});
	}
	$('.upeng_slide_status').change(function(){
		if($(this).val() == 0){
			$('div.stupload-form-slide').css({'display' : 'block'});
		}else{
			$('div.stupload-form-slide').css({'display' : 'none'});
		}
	});

	// for video file
	if($('.upeng_video_status').val() == 0){
		$('div.stupload-form-video').css({'display' : 'block'});
	}
	$('.upeng_video_status').change(function(){
		if($(this).val() == 0){
			$('div.stupload-form-video').css({'display' : 'block'});
		}else{
			$('div.stupload-form-video').css({'display' : 'none'});
		}
	});

	// for codefile file
	if($('.upeng_codefile_status').val() == 0){
		$('div.stupload-form-codefile').css({'display' : 'block'});
	}
	$('.upeng_codefile_status').change(function(){
		if($(this).val() == 0){
			$('div.stupload-form-codefile').css({'display' : 'block'});
		}else{
			$('div.stupload-form-codefile').css({'display' : 'none'});
		}
	});
	// for assignment file
	if($('.upeng_asgmnt_status').val() == 0){
		$('div.stupload-form-asgmnt').css({'display' : 'block'});
	}
	$('.upeng_asgmnt_status').change(function(){
		if($(this).val() == 0){
			$('div.stupload-form-asgmnt').css({'display' : 'block'});
		}else{
			$('div.stupload-form-asgmnt').css({'display' : 'none'});
		}
	});

// Other languages 

$('.uolang_foss_category_name').change(function(){
		foss = $(this).val();
		$.ajax({
			type : 'POST',
			url : webroot + "get_category_levels",
			data : {
				'foss' : foss
			},
			beforeSend: function() {
			    field_data = $('.uolang-level-name').html();
			    $('.uolang-level-name').html(loading_image);
			},
			success : function(data){
				output = JSON.parse(data);
				var html_data = "<option value=''>-- Select --</option>";
				if(output){
					$('.uolang-level-name').html(field_data);
					for (var i=0; i < output.length; i++)
					{
						html_data += "<option value='"+ output[i].tutorial_level +"'>" + output[i].tutorial_level + "</option>";	
					}
					$('.uolang_tutorial_level').html(html_data);

					// adding the tutorial languages under tutorial level
					// $('.uolang_tutorial_level').change(function(){
					// 	level = $(this).val();;
					// 	foss = $('.uolang_foss_category_name').val();
					// 	$.ajax({
					// 		type : 'POST',
					// 		url : webroot + "get_languages",
					// 		data : {
					// 			'level' : level,
					// 			'foss' : foss
					// 		},
					// 		beforeSend: function() {
					// 		    field_data = $('.uolang-lang').html();
					// 		    $('.uolang-lang').html(loading_image);
					// 		},
					// 		success : function(data){
					// 			output = JSON.parse(data);
					// 			console.log(output);
					// 			var html_data = "<option value=''>Tutorial name</option>";
					// 			if(output){
					// 				$('.uolang-lang').html(field_data);
					// 				for (var i=0; i < output.length; i++)
					// 				{
					// 					html_data += "<option value='"+ output[i].name +"'>" + output[i].name + "</option>";	
					// 				}
					// 				$('.uolang_tutorial_lang').html(html_data);

									// get tutorial names under selected foss, level and languages
									$('.uolang_tutorial_lang').change(function(){
										lang = $(this).val();;
										foss = $('.uolang_foss_category_name').val();
										level = $('.uolang_tutorial_level').val();
										flag = $('.upload_flag').val();
										$.ajax({
											type : 'POST',
											url : webroot + "get_olang_tnames",
											data : {
												'level' : level,
												'foss' : foss,
												'lang' : lang,
												'flag' : flag
											},
											beforeSend: function() {
											    field_data = $('.uolang-name').html();
											    $('.uolang-name').html(loading_image);
											},
											success : function(data){
												output = JSON.parse(data);
												console.log(output);
												var html_data = "<option value=''>-- Select --</option>";
												if(output){
													$('.uolang-name').html(field_data);
													for (var i=0; i < output.length; i++)
													{
														html_data += "<option value='"+ output[i].tutorial_name +"'>" + output[i].tutorial_name + "</option>";	
													}
													$('.uolang_tutorial_name').html(html_data);
													// get tutorial names under selected foss, level and languages
													
												}else{
													alert('Somthing wrong, Please refresh page');
												}
											}
										});
									});
						// 		}else{
						// 			alert('Somthing wrong, Please refresh page');
						// 		}
						// 	}
						// });
					// });
				}else{
					alert('Somthing wrong, Please refresh page');
				}
			}
		});
	});

	// review tutorial
	$('.reviewer-comment').css({'display': 'none'});
	$('#edit-status-under-review, #edit-status-pending, #edit-status-need-improvement, #edit-status-accepted, #edit-status-need-improvement').click(function(){
		if($(this).val() == 'need_improvement'){
			$('.reviewer-comment').css({'display': 'block'});
		}else{
			$('.reviewer-comment').css({'display': 'none'});
		}
	});
	// foss category
	$('.foss_category_add').change(function(){
		if($(this).val() == 'addnew'){
			$('.aable-foss-name').css({'display':'block'});
		}else{
			$('.aable-foss-name').css({'display':'none'});
		}
	});

});
