$(function(){


	function sendForm(btn, form){
		var loader = btn.children('.loader');

		$.ajaxPrefilter(function( options, _, jqXHR ) {
            if ( options.onreadystatechange ) {
                var xhrFactory = options.xhr;
                options.xhr = function() {
                    var xhr = xhrFactory.apply( this, arguments );
                    function handler() {
                        options.onreadystatechange( xhr, jqXHR );
                    }
                    if ( xhr.addEventListener ) {
                        xhr.addEventListener( "readystatechange", handler, false );
                    } else {
                        setTimeout( function() {
                            var internal = xhr.onreadystatechange;
                            if ( internal ) {
                                xhr.onreadystatechange = function() {
                                    handler();
                                    internal.apply( this, arguments ); 
                                };
                            }
                        }, 0 );
                    }
                    return xhr;
                };
            }
        });

		var xhr = $.ajax({
			beforeSend: function(){
				loader.text('\\/')
			},
			url: btn.data('action'),
			type: 'POST',
			data: new FormData(form),
	        cache: false,
	        contentType: false,
	        processData: false,
	        dataType: 'json',
	        onreadystatechange: function(xhr){
	        	if(xhr.readyState === 3){
	        		data = xhr.responseText
	        		try{
	        			data = JSON.parse(xhr.responseText)
	        		}catch(e){
	        			console.err('Could not parse json response')
	        		}
		        	console.log(data)
		        }
	        },
			success: function(res){
				if(res.zip_id){
					iframe = $('#download_iframe')[0]
					iframe.src = '/modes-of-operation/get_zip/'+res.zip_id+'/'
				}else{
					alert('No se obtuvo zip')
				}
			},
			error: function(errs){
				console.log('Error en comunicación con el servidor');
			},
			complete: function(jqxhr, txt){
				loader.text('');
				$('.img-sd').text('No se ha selecc...')
				form.reset()
			}
		})

	}

	$('.opmodes-sub').on('click', function(e){
		e.preventDefault();
		var $elf = $(this);
		var _type = $elf.data('type');
		var form  = $('#opmodes-form');
		if( _type === 'decrypt'){
			alert('Mostar tipos');
		}else{
			//form.attr('action', $elf.data('action'))
			//form.submit()
			sendForm($elf, form[0])
		}

	})

	$('.file_cvr').on('click', function(e){
		e.preventDefault();
		$elf = $(this);
		file_input = $($elf.data('input'))

		file_input.click()
		file_input.on('change', function(){
			$('.img-sd').text('Archivo: '+$(this).val().replace('C:\\fakepath','.../'))
		})
	})
})