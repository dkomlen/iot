import base64
from google.cloud import monitoring_v3
import time

def create_metric_descriptor(project_id, name):
    client = monitoring_v3.MetricServiceClient()
    project_name = client.project_path(project_id)
    descriptor = monitoring_v3.types.MetricDescriptor()
    descriptor.type = 'custom.googleapis.com/photon_' + name
    descriptor.metric_kind = (
        monitoring_v3.enums.MetricDescriptor.MetricKind.GAUGE)
    descriptor.value_type = (
        monitoring_v3.enums.MetricDescriptor.ValueType.DOUBLE)
    descriptor.description = 'Photon custom metric for ' + name
    descriptor = client.create_metric_descriptor(project_name, descriptor)
    print('Created {}.'.format(descriptor.name))

def handler(event, context):
    """Triggered from a message on a Cloud Pub/Sub topic.
    Args:
         event (dict): Event payload.
         context (google.cloud.functions.Context): Metadata for the event.
    """
    
    msg = base64.b64decode(event['data']).decode('utf-8')
    vals = {item[0].strip():item[1].strip() for item in (ms.split(':') for ms in msg.split(','))}
    print(vals)

    client = monitoring_v3.MetricServiceClient()
    project = 'photon-playground'
    project_name = client.project_path(project)

    for name, val in vals.items():
        series = monitoring_v3.types.TimeSeries()
        series.metric.type = 'custom.googleapis.com/' + name
        series.resource.type = 'global'
        series.resource.labels['project_id'] = project
        
        point = series.points.add()
        point.value.double_value = float(val)
        now = time.time()
        point.interval.end_time.seconds = int(now)
        point.interval.end_time.nanos = int(
                (now - point.interval.end_time.seconds) * 10**9)
        client.create_time_series(project_name, [series])
        print('Successfully wrote time series.')
