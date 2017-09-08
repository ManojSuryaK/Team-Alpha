import json
import mimetypes

from .watson_developer_cloud_service import WatsonDeveloperCloudService


class VisualRecognitionV3(WatsonDeveloperCloudService):
    """using Visual Recognition for image recognition"""
    default_url = 'https://gateway-a.watsonplatform.net/visual-recognition/api'
    latest_version = '2016-05-20'

    def __init__(self, version, url=default_url, **kwargs):
        """initiating the service instance called with the version of
            of the api and the URL of the api"""
        WatsonDeveloperCloudService.__init__(self, 'watson_vision_combined',
                                             url, **kwargs)
        self.version = version

    def get_classifier(self, classifier_id):
        """
        Fetches the details of a particular classifier using classifier_id
        """

        params = {'version': self.version}
        return self.request(method='GET',
                            url='/v3/classifiers/{0}'.format(classifier_id),
                            params=params,
                            accept_json=True)

    def delete_classifier(self, classifier_id):
        """
        To delete a particular custom created classifier using classifier_id
        """

        params = {'version': self.version}
        return self.request(method='DELETE',
                            url='/v3/classifiers/{0}'.format(classifier_id),
                            params=params,
                            accept_json=True)

    def list_classifiers(self, verbose=False):
        """
        returns a list of the available classifiers,both custom and built-in 
        """

        params = {'verbose': verbose, 'version': self.version}
        return self.request(method='GET', url='/v3/classifiers', params=params,
                            accept_json=True)

    def create_classifier(self, name, **kwargs):
        """
        trains a new classifier with the given classifier positive
        and negative data sets
        """

        params = {'version': self.version}
        data = {'name': name}
        # Params sent as url parameters here
        return self.request(method='POST', url='/v3/classifiers', files=kwargs,
                            data=data, params=params,
                            accept_json=True)

    def update_classifier(self, classifier_id, **kwargs):
        """
        Updates a data classifier with new images ,uses parameters - classifier id 
        """

        params = {'version': self.version}
        # Params sent as url parameters here
        return self.request(method='POST',
                            url='/v3/classifiers/{0}'.format(classifier_id),
                            files=kwargs,
                            params=params, accept_json=True)

    def _image_call(self, url, images_file=None, images_url=None, params=None):
        """classify a test image by passing its image_url or the image path
            to a particular classifier_id
        """
        if images_file is None and images_url is None:
            raise AssertionError('You must specify either a file or a url')

        if images_url:
            params['url'] = images_url
            return self.request(method='GET', url=url, params=params,
                                accept_json=True)
        filename = images_file.name
        mime_type = mimetypes.guess_type(
            filename)[0] or 'application/octet-stream'

        if 'zip' in mime_type:
            mime_type = 'application/zip'

        filename = filename.replace('\\', '/')

        return self.request(method='POST', url=url,
                            files={'images_file': (
                                filename, images_file, mime_type)},
                            params=params,
                            accept_json=True)

    def classify(self, images_file=None, images_url=None, classifier_ids=None,
                 owners=None, threshold=None):
        """
        Returns a list of the scores of the image classification 
        """

        if isinstance(classifier_ids, list):
            classifier_ids = ','.join(classifier_ids)
        if isinstance(owners, list):
            owners = ','.join(owners)

        params = {'version': self.version, 'classifier_ids': classifier_ids,
                  'owners': owners, 'threshold': threshold}
        return self._image_call('/v3/classify', images_file, images_url,
                                params) 
